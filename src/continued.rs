use std::{fmt::Display, mem::swap, ops::SubAssign};

pub struct ContinuedFraction {
    terms: Vec<u8>
}

impl ContinuedFraction {
    pub fn new(numerator: u128, denominator: u128) -> Self {
        let mut n = numerator;
        let mut d = denominator; 
        let mut terms: Vec<u16> = Vec::new();

        loop {
            terms.push((n / d) as u16);
            n -= (n / d) * d;
            if n == 0 { break }
            swap(&mut n, &mut d);       
        } 
        
        if terms.len() % 2 == 0     {
            terms.last_mut().unwrap().sub_assign(1);
            terms.push(1);
        }

        println!("{:?}", terms);

        return Self{terms: Vec::new()};
    }

    pub fn to_frac(&self) -> (u64, u64) {
        let mut n = 1;
        let mut d = u64::from(*self.terms.last().unwrap());


        for term in self.terms.iter().rev().skip(1) {
            n += u64::from(*term) * d;
            swap(&mut n, &mut d);
        }

        swap(&mut n, &mut d);
        return (n, d);
    }

    pub fn to_binary(&self) -> u64 {
        let mut num = !0;

        self.terms.iter().rev().for_each(|x| {
            num <<= x;
            num = !num;
        });

        return num;
    }

    pub fn from_binary(n: u64) -> Self {
        let mut num = n;
        let mut terms: Vec<u8> = Vec::new();

        loop {
            let c = if terms.len() % 2 == 0 {
                u8::try_from(num.trailing_ones()).unwrap()
            } else {
                u8::try_from(num.trailing_zeros()).unwrap()
            };
            terms.push(c);
            num >>= c;
            if num == 0 { break }
        }

        return Self{terms}
    }

    pub fn fusc(n: u64) -> u64 {
        return Self::from_binary(n).to_frac().0;
    }
}

impl Display for ContinuedFraction {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        return f.write_fmt(format_args!("{:?}", self.terms));
    }
}


pub fn fusc(n: u64) -> u64 {
    let mut num = n;
    let mut terms: Vec<u8> = Vec::new();

    loop {
        let c = if terms.len() % 2 == 0 {
            num.trailing_ones() as u8
        } else {
            num.trailing_zeros() as u8
        };

        terms.push(c);
        num >>= c;
        if num == 0 { break }
    }

    let mut numerator = u64::from(*terms.last().unwrap());
    let mut denominator = 1;

    for term in terms.iter().rev().skip(1) {
        swap(&mut numerator, &mut denominator);
        numerator += u64::from(*term) * denominator;
    }

    return numerator;
}

pub fn fusc_optimized(n: u64) -> u64 {
    let mut num = n;
    let mut terms: Vec<u8> = Vec::with_capacity(64);

    let c = num.trailing_ones() as u8;
    terms.push(c);
    num >>= c;
    
    while num != 0 {
        let c = num.trailing_zeros() as u8;
        terms.push(c);
        num >>= c;

        let c = num.trailing_ones() as u8;
        terms.push(c);
        num >>= c;
    }

    let mut numerator = u64::from(*terms.last().unwrap());
    let mut denominator = 1;

    for term in terms.iter().rev().skip(1) {
        swap(&mut numerator, &mut denominator);
        numerator += u64::from(*term) * denominator;
    }

    return numerator;
}