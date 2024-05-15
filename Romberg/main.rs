const EPSILON: f64 = 1e-7;
const MAX_ITERATIONS: usize = 20;

fn f1(x: f64) -> f64 {
    x.sin() / x
}
fn f2(x: f64) -> f64 {
    (-x * x).exp()
}
fn f3(x: f64) -> f64 {
    if x != 0.0 {
        (1.0 + x).ln() / x
    } else {
        1.0
    }
}
fn trapezoidal(a: f64, b: f64, n: i32, f: fn(f64) -> f64) -> f64 {
    let h = (b - a) / (n as f64);
    let mut sum = 0.5 * (f(a) + f(b));
    for i in 1..n {
        sum += f(a + i as f64 * h);
    }
    h * sum
}

fn simpson(a: f64, b: f64, n: i32, f: fn(f64) -> f64) -> f64 {
    let h = (b - a) / (n as f64);
    let mut sum = f(a) + f(b) + 4.0 * f(a + 0.5 * h);
    for i in 1..n {
        sum += 2.0 * f(a + i as f64 * h) + 4.0 * f(a + (i as f64 + 0.5) * h);
    }
    h / 6.0 * sum
}

fn integral(a: f64, b: f64, f: fn(f64) -> f64, method: fn(f64, f64, i32, fn(f64) -> f64) -> f64) {
    let mut result = method(a, b, 1, f);
    let mut i = 1;
    let mut new_result;
    loop {
        new_result = method(a, b, 1 << i, f);
        if (result.abs() <= 100.0 && (result - new_result).abs() < EPSILON)
            || (result.abs() > 100.0 && ((result - new_result) / new_result).abs() < EPSILON)
        {
            break;
        }
        result = new_result;
        i += 1;
    }
    let ans1 = 1 << i;
    let ans2 = if method == trapezoidal {
        ans1 + 1
    } else {
        (ans1 << 1) + 1
    };
    println!(
        "积分结果: {:.8}\n区间个数: {}\n基点个数: {}",
        result, ans1, ans2
    );
}
fn main() {
    let func_ptr: [fn(f64) -> f64; 3] = [f1, f2, f3];
    let range: [[f64; 2]; 3] = [[0.1, 4.0], [-2.0, 4.0], [0.0, 1.0]];

    for (i, &start_end) in range.iter().enumerate() {
        let start = start_end[0];
        let end = start_end[1];
        println!("----------------------------------------------------------------------");
        println!(
            "|                         测试 {} 开始！                              ｜",
            i + 1
        );
        println!("----------------------------------------------------------------------");
        println!("\n复合梯形公式：");
        integral(start, end, func_ptr[i], trapezoidal);
        println!("\n复合Simpson公式：");
        integral(start, end, func_ptr[i], simpson);
        println!("\n龙贝格积分法：");
        let mut t = [[0.0; MAX_ITERATIONS]; 2];
        t[0][0] = trapezoidal(start, end, 1, func_ptr[i]);
        println!("T[0][0] = {:.8}", t[0][0]);
        for j in 1..MAX_ITERATIONS {
            t[1][0] = trapezoidal(start, end, 1 << j, func_ptr[i]);
            print!("T[{}][0] = {:.8} ", j, t[1][0]);
            for k in 1..=j {
                t[1][k] = t[1][k - 1] + (t[1][k - 1] - t[0][k - 1]) / ((1 << (2 * k)) as f64 - 1.0);
                print!("T[{}][{}] = {:.8} ", j, k, t[1][k]);
            }
            println!();
            if (t[1][j].abs() <= 100.0 && (t[1][j] - t[0][j - 1]).abs() < EPSILON)
                || (t[1][j].abs() > 100.0 && ((t[1][j] - t[0][j - 1]) / t[1][j]).abs() < EPSILON)
            {
                println!("积分结果: {:.8}\n", t[1][j]);
                break;
            }
            for k in 0..=j {
                t[0][k] = t[1][k];
            }
        }
    }
}
