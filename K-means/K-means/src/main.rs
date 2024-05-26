extern crate csv;
extern crate linfa;
extern crate linfa_clustering;
extern crate ndarray;
extern crate plotters;

use linfa::prelude::*;
use linfa_clustering::KMeans;
use ndarray::{Array1, Array2};
use plotters::prelude::*;
use std::error::Error;

// 加载并标准化数据集
fn load_iris() -> Result<(Array2<f64>, Array1<u8>), Box<dyn Error>> {
    let mut rdr = csv::Reader::from_path(
        "/Users/frazier/Downloads/8836201-6f9306ad21398ea43cba4f7d537619d0e07d5ae3/iris.csv",
    )?;
    let mut data = Vec::new();
    let mut target = Vec::new();

    for result in rdr.records() {
        let record = result?;
        let features: Vec<f64> = record.iter().take(4).map(|x| x.parse().unwrap()).collect();
        let label: u8 = match &record[4] as &str {
            "Iris-setosa" => 0,
            "Iris-versicolor" => 1,
            "Iris-virginica" => 2,
            _ => panic!("Unknown label"),
        };
        data.extend_from_slice(&features);
        target.push(label);
    }

    let n_samples = target.len();
    let data = Array2::from_shape_vec((n_samples, 4), data)?;
    let target = Array1::from(target);
    Ok((data, target))
}

fn main() -> Result<(), Box<dyn Error>> {
    let (data, target) = load_iris()?;

    // 将数据集转换为 linfa 数据集类型
    let dataset = Dataset::new(data.clone(), target.clone());

    // 使用 linfa 库中的 KMeans 实现
    let n_clusters = 3;
    let model = KMeans::params(n_clusters).fit(&dataset)?;

    // 获取聚类结果
    let centroids = model.centroids();
    let predictions = model.predict(&dataset);

    // 计算总内聚度（SSE）
    let inertia: f64 = model.inertia();
    println!("Total Inertia: {}", inertia);

    // 可视化聚类结果
    let root_area = BitMapBackend::new("kmeans.png", (1024, 768)).into_drawing_area();
    root_area.fill(&WHITE)?;
    let mut chart = ChartBuilder::on(&root_area)
        .caption("K-Means Clustering", ("sans-serif", 50).into_font())
        .margin(10)
        .x_label_area_size(40)
        .y_label_area_size(40)
        .build_cartesian_2d(-3.0..3.0, -3.0..3.0)?;

    chart.configure_mesh().draw()?;

    let colors = &[&RED, &GREEN, &BLUE];
    for (i, &cluster) in predictions.iter().enumerate() {
        let x = data[[i, 0]];
        let y = data[[i, 1]];
        chart.draw_series(PointSeries::of_element(
            vec![(x, y)],
            5,
            colors[cluster as usize],
            &|c, s, st| EmptyElement::at(c) + Circle::new((0, 0), s, st.filled()),
        ))?;
    }

    for (i, centroid) in centroids.outer_iter().enumerate() {
        let x = centroid[0];
        let y = centroid[1];
        chart.draw_series(PointSeries::of_element(
            vec![(x, y)],
            10,
            colors[i],
            &|c, s, st| EmptyElement::at(c) + Cross::new((0, 0), s, st.filled()),
        ))?;
    }

    Ok(())
}
