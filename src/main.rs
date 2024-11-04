pub mod rational;
pub mod continued;

use std::time::Instant;

use continued::ContinuedFraction;

fn main() {
    let pi = ContinuedFraction::new(884279719003555/35, 281474976710655/35);
    println!("{pi}");
}
