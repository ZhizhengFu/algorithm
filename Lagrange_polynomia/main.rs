use std::io::{self, Write};

fn main() {
    let (x, y) = read_input();
    let k = x.len();
    let param = lagrange(&x, &y, k);
    println!("\nThe Lagrange polynomial is:");
    for (i, &coeff) in param.iter().enumerate() {
        print!("{}", coeff);
        if i != 0 {
            print!("x^{}", i);
        }
        if i != k - 1 {
            print!(" + ");
        }
    }
    println!("\n");

    loop {
        evaluate_polynomial(&param);
    }
}

fn read_input() -> (Vec<f64>, Vec<f64>) {
    let mut input = String::new();
    println!("Enter the number of points:");
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line");
    let k: usize = input.trim().parse().expect("Please type a number!");

    let mut x = vec![0.0; k];
    let mut y = vec![0.0; k];

    println!("Enter x:");
    for i in 0..k {
        input.clear();
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read line");
        x[i] = input.trim().parse().expect("Please type a number!");
    }

    println!("Enter y:");
    for i in 0..k {
        input.clear();
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read line");
        y[i] = input.trim().parse().expect("Please type a number!");
    }

    (x, y)
}

fn lagrange(x: &[f64], y: &[f64], k: usize) -> Vec<f64> {
    let mut param = vec![0.0; k];
    for i in 0..k {
        let l_i = l(x, i, k);
        for j in 0..k {
            param[j] += y[i] * l_i[j];
        }
    }
    param
}

fn l(x: &[f64], j: usize, k: usize) -> Vec<f64> {
    let mut temp = vec![0.0; k];
    let mut t1 = 1.0;
    temp[0] = 1.0;
    let mut count = 0;

    for i in 0..k {
        if i == j {
            continue;
        }
        t1 *= 1.0 / (x[j] - x[i]);
        let t2 = -x[i];
        temp[count + 1] = 1.0;
        for k in (1..=count).rev() {
            temp[k] = temp[k - 1] + t2 * temp[k];
        }
        temp[0] = t2 * temp[0];
        count += 1;
    }
    for val in &mut temp {
        *val *= t1;
    }
    temp
}

fn evaluate_polynomial(param: &[f64]) {
    let mut input = String::new();
    println!("CTRL+C to exit or Enter a point to evaluate:");
    io::stdin()
        .read_line(&mut input)
        .expect("Failed to read line");
    let t1: f64 = input.trim().parse().expect("Please type a number!");

    let mut t2 = 0.0;
    for (i, &coeff) in param.iter().enumerate() {
        let t3 = t1.powi(i as i32);
        t2 += coeff * t3;
    }
    println!("The value of the polynomial at {} is {}", t1, t2);
}
