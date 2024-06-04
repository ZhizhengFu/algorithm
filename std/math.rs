fn inv_sqrt(x: f32) -> f32 {
    let y = f32::from_bits(0x5f3759df - (x.to_bits() >> 1));
    let y = y * (1.5 - 0.5 * x * y * y);
    y * (1.5 - 0.5 * x * y * y)
}
