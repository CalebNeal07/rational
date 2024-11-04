use std::{fmt::{Debug, Display}, ops::Mul};

#[derive(Clone, Copy)]
pub struct Rational16(u16);

impl Rational16 {
    pub fn create_raw(val: u16) -> Self {
        return Rational16(val);
    }
}

impl Debug for Rational16 {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        return f.write_fmt(format_args!("{:016b}", self.0));
    }
}

impl Display for Rational16 {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        return f.write_fmt(format_args!("{:016b}", self.0));
    }
}

impl Mul for Rational16 {
    type Output = Rational16;

    fn mul(self, rhs: Self) -> Self::Output {
        let mut ret = self.0;

        ret ^= rhs.0;

        return Rational16::create_raw(ret);
    }
}