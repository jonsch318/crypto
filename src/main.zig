const std = @import("std");
const math = @import("util/math.zig");

test {
    std.testing.refAllDecls(@This());
    std.testing.refAllDecls(math);
}
