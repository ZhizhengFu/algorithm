fn main() {
    let mut a: [f64; 4] = [1.0; 4];
    let mut b: [f64; 4] = [2.0; 4];
    let c: [f64; 4] = [3.0; 4];
    let mut d: [f64; 4] = [1.0, 0.0, 3.0, 2.0];
    let n = a.len();
    a[0] *= -1.0;
    for i in 1..n - 1 {
        a[i] /= b[i - 1];
        b[i] -= a[i] * c[i - 1];
        d[i] -= a[i] * d[i - 1];
        a[i] *= -a[i - 1];
    }
    a[n - 2] = (a[n - 2] - c[n - 2]) / b[n - 2];
    d[n - 2] /= b[n - 2];
    for i in (0..n - 2).rev() {
        a[i] = (a[i] - c[i] * a[i + 1]) / b[i];
        d[i] = (d[i] - c[i] * d[i + 1]) / b[i];
    }
    a[n - 1] = (d[n - 1] - c[n - 1] * d[0] - a[n - 1] * d[n - 2])
        / (b[n - 1] + a[n - 1] * a[n - 2] + c[n - 1] * a[0]);
    for i in 0..n - 1 {
        println!("x{} = {}", i + 1, d[i] + a[i] * a[n - 1]);
    }
    println!("x{} = {}", n, a[n - 1]);
}
