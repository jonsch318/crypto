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
