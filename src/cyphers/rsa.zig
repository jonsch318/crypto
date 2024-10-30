//! RSA encryption and decryption
const std = @import("std");
const math = @import("../util//math.zig");

pub fn generateKey(comptime T: type, p: anytype, q: anytype) struct { secret: T, public: struct { modulus: T, exponent: T } } {
    const sT = @TypeOf(-std.math.maxInt(T));
    const N = p * q;
    const lambda_n = math.lcm(p - 1, q - 1);
    const e = 65537;
    const t = math.extendedGcd(sT, e, lambda_n);
    var d: T = @abs(t.coefficients.x);
    if (t.coefficients.x < 0) {
        d = @mod((lambda_n + t.coefficients.x), lambda_n);
    }
    return .{ .secret = @intCast(d), .public = .{ .modulus = N, .exponent = e } };
}

test "key generation" {
    const res1 = generateKey(u64, 11, 13);
    try std.testing.expect(res1.secret == 53);
    try std.testing.expect(res1.public.modulus == 143);
    try std.testing.expect(res1.public.exponent == 65537);

    const res2 = generateKey(u128, 8191, 20639);
    try std.testing.expect(res2.secret == 25272413);
    try std.testing.expect(res2.public.modulus == 169054049);
    try std.testing.expect(res2.public.exponent == 65537);

    const res3 = generateKey(u128, 20983, 22907);
    try std.testing.expect(res3.secret == 1699955);
    try std.testing.expect(res3.public.modulus == 480657581);
    try std.testing.expect(res3.public.exponent == 65537);
}

pub fn encrypt(comptime T: type, e: T, modulus: T, v: u8) T {
    return math.modPow(T, v, e, modulus);
}

pub fn decrypt(comptime T: type, d: T, modulus: T, v: T) u8 {
    return @intCast(math.modPow(T, v, d, modulus));
}

test "en-/decrypt" {
    const rand = std.crypto.random;
    for (0..128) |_| {
        const v: u8 = rand.int(u8);
        const enc = encrypt(u64, 65537, 480657581, v);
        const dec = decrypt(u64, 1699955, 480657581, enc);
        try std.testing.expectEqual(v, dec);
    }
}

pub fn encryptBytes(comptime T: type, allocator: std.mem.Allocator, e: T, modulus: T, s: []const u8) ![]T {
    var result = try allocator.alloc(T, s.len);
    for (0..s.len) |i| {
        result[i] = encrypt(T, e, modulus, s[i]);
    }
    return result;
}

pub fn decryptBytes(comptime T: type, allocator: std.mem.Allocator, d: T, modulus: T, s: []const T) ![]u8 {
    var result = try allocator.alloc(u8, s.len);
    for (0..s.len) |i| {
        result[i] = decrypt(T, d, modulus, s[i]);
    }
    return result;
}

test "en-/decrypt string" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();
    const rand = std.crypto.random;
    for (0..8) |_| {
        const s = [_]u8{ rand.intRangeAtMost(u8, 'a', 'z'), rand.intRangeAtMost(u8, 'a', 'z'), rand.intRangeAtMost(u8, 'a', 'z'), rand.intRangeAtMost(u8, 'a', 'z'), rand.intRangeAtMost(u8, 'a', 'z') };
        const enc = try encryptBytes(u64, allocator, 65537, 480657581, &s);
        const dec = try decryptBytes(u64, allocator, 1699955, 480657581, enc);
        try std.testing.expectEqualStrings(&s, dec);
    }
}
