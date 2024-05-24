const X0: f64 = 0.0;
const Y0: f64 = 2.0;
const H: f64 = 0.1;
const XN: f64 = 5.0;

fn accu_f(x: f64) -> f64 {
    (4.0 * x.powi(3) + 6.0) / (3.0 * x.powi(2) + 3.0)
}

fn f(x: f64, y: f64) -> f64 {
    (4.0 * x.powi(2) - 2.0 * x * y) / (1.0 + x.powi(2))
}

fn runge_kutta(x: f64, y: f64) -> f64 {
    let k1 = H * f(x, y);
    let k2 = H * f(x + H / 2.0, y + k1 / 2.0);
    let k3 = H * f(x + H / 2.0, y + k2 / 2.0);
    let k4 = H * f(x + H, y + k3);
    y + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0
}

fn adams_pece(y: &[f64; 4], x: f64) -> f64 {
    let y_pred = y[3]
        + H / 24.0
            * (55.0 * f(x, y[3]) - 59.0 * f(x - H, y[2]) + 37.0 * f(x - 2.0 * H, y[1])
                - 9.0 * f(x - 3.0 * H, y[0]));
    y[3] + H / 24.0
        * (9.0 * f(x + H, y_pred) + 19.0 * f(x, y[3]) - 5.0 * f(x - H, y[2]) + f(x - 2.0 * H, y[1]))
}

fn main() {
    println!("i\txi\tyi\ty(xi)\ty(xi)-yi");
    let mut y = [Y0; 4];
    for i in 1..=((XN / H) as i32) {
        let xi = X0 + i as f64 * H;
        if i < 4 {
            y[i as usize] = runge_kutta(xi - H, y[(i - 1) as usize]);
        } else {
            let next_y = adams_pece(&y, xi - H);
            y.rotate_left(1);
            y[3] = next_y;
        };
        println!(
            "{}\t{:.1}\t{:.6}\t{:.6}\t{:.6}",
            i,
            xi,
            y[if i < 4 { i as usize } else { 3 }],
            accu_f(xi),
            accu_f(xi) - y[if i < 4 { i as usize } else { 3 }]
        );
    }
}
