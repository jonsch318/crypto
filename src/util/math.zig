//! Math utilities.
const std = @import("std");

/// Returns the least common multiple of two numbers.
pub fn lcm(a: anytype, b: anytype) @TypeOf(a, b) {
    const x = @abs(a);
    const y = @abs(b);
    const N = switch (@TypeOf(x, y)) {
        comptime_int => std.math.IntFittingRange(@min(x, y), @max(x, y)),
        else => |T| T,
    };
    if (@typeInfo(N) != .int or @typeInfo(N).int.signedness != .unsigned) {
        @compileError("`a` and `b` must be usigned integers");
    }
    if (x == 0 and y == 0) {
        return 0;
    }
    return x * (y / std.math.gcd(x, y));
}

test "lcm" {
    try std.testing.expect(lcm(6, 8) == 24);
    try std.testing.expect(lcm(6, -8) == 24);
    try std.testing.expect(lcm(0, 5) == 0);
    try std.testing.expect(lcm(-6, -8) == 24);
    try std.testing.expect(lcm(7, 7) == 7);
    try std.testing.expect(lcm(1, 10) == 10);
    try std.testing.expect(lcm(123456, 789012) == 8117355456);
    try std.testing.expect(lcm(330435143123456, 7521321343321) == 2485308894557778977664037376);
    try std.testing.expect(lcm(98165387439658732946587236459874326543287567895868767, 483975294398432057098437294378564328750432658743265874320) == 47509622285844979790940371549421128101843985857290138563642804349113088635190746305513659518301947820235363440);
}

/// computes the extended greatest common divisor of two numbers
pub fn extendedGcd(comptime T: type, a: anytype, b: anytype) struct { gcd: T, coefficients: struct { x: T, y: T } } {
    if (a == 0) {
        return .{ .gcd = b, .coefficients = struct { .x = 0, .y = 1 } };
    }
    var local_a: T = @intCast(a);
    var local_b: T = @intCast(b);
    var prevX: T = 1;
    var prevY: T = 0;
    var currX: T = 0;
    var currY: T = 1;
    while (local_b != 0) {
        const bn = @divFloor(local_a, local_b);
        const newB = @mod(local_a, local_b);
        local_a = local_b;
        local_b = newB;
        const newX = prevX - bn * currX;
        const newY = prevY - bn * currY;
        prevX = currX;
        prevY = currY;
        currX = newX;
        currY = newY;
    }

    return .{ .gcd = local_a, .coefficients = .{ .x = prevX, .y = prevY } };
}

test "extended gcd" {
    const res1 = extendedGcd(i32, 99, 78);
    try std.testing.expect(res1.gcd == 3);
    try std.testing.expect(res1.coefficients.x == -11);
    try std.testing.expect(res1.coefficients.y == 14);

    const res2 = extendedGcd(i32, 48, 18);
    try std.testing.expect(res2.gcd == 6);
    try std.testing.expect(res2.coefficients.x == -1);
    try std.testing.expect(res2.coefficients.y == 3);

    const res3 = extendedGcd(i32, 101, 103);
    try std.testing.expect(res3.gcd == 1);
    try std.testing.expect(res3.coefficients.x == 51);
    try std.testing.expect(res3.coefficients.y == -50);

    const res4 = extendedGcd(i32, 270, 192);
    try std.testing.expect(res4.gcd == 6);
    try std.testing.expect(res4.coefficients.x == 5);
    try std.testing.expect(res4.coefficients.y == -7);

    const res5 = extendedGcd(i32, 56, 98);
    try std.testing.expect(res5.gcd == 14);
    try std.testing.expect(res5.coefficients.x == 2);
    try std.testing.expect(res5.coefficients.y == -1);

    const res6 = extendedGcd(i32, 123456, 789012);
    try std.testing.expect(res6.gcd == 12);
    try std.testing.expect(res6.coefficients.x == 22963);
    try std.testing.expect(res6.coefficients.y == -3593);

    const res7 = extendedGcd(i32, 17, 31);
    try std.testing.expect(res7.gcd == 1);
    try std.testing.expect(res7.coefficients.x == 11);
    try std.testing.expect(res7.coefficients.y == -6);

    const res8 = extendedGcd(i512, 1754298765872346584329765987423, 324541353254325432543251);
    try std.testing.expect(res8.gcd == 1);
    try std.testing.expect(res8.coefficients.x == 63872172236815977368617);
    try std.testing.expect(res8.coefficients.y == -345259153587198005977872461490);
}

/// Computes the modular exponentiation of a number.
pub fn modPow(comptime T: type, v: T, e: T, m: T) T {
    var c: T = 1;
    var i: T = 0;
    while (i < e) : (i += 1) {
        c = @mod(v * c, m);
    }
    return c;
}

test "modPow" {
    try std.testing.expectEqual(6214, modPow(u64, 41213, 1451435, 13123));
    try std.testing.expectEqual(92, modPow(u64, 41213, 1451435, 131));
    try std.testing.expectEqual(127728, modPow(u64, 5243652, 1451435, 131312));
}
