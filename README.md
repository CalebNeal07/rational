# Rational
> This repositroy implements storing rational numbers by their position in the Calkin-Wilf Sequence 

The [Calkin-Wilf Sequence](https://en.wikipedia.org/wiki/Calkin%E2%80%93Wilf_tree#Breadth_first_traversal) 
is given by the expression $a_n=\frac{fusc(n)}{fusc(n+1)}$ where $fusc(n)$ is the recursive function 
where $fusc(2n)=fusc(n)$ and $fusc(2n+1)=fusc(n)+fusc(n+1)$ where $fusc(0)=0$ and $fusc(1)=1$.[^1]

This sequence of interest because the run length encoding og the binary representation 
of a number in the Calkin-Wilf Sequence is equivalent to the odd continued fraction representation 
of the rational it represents. Additionally, as Dijkstra notes, the inner values, all values 
excluding the most and least signfigant digits, can be inverted and the value will be the same 
when submitted to the $fusc$ function.[^2]

Stern's Diatomic Sequence can be generated with the following excerpt of python code:
```python
from collections import deque
from itertools import islice, count

n = 2000

def fusc():
    q = deque([1])
    yield 0
    yield 1

    while True:
        x = q.popleft()
        q.append(x)
        yield x

        x += q[0]
        q.append(x)
        yield x

# Generates the members of stern's diatomic sequence up to n
sds = list(islice(fusc(), n)) 

print(sds)
```

From Stern's Diatomic Sequence it is trivial to generate the Calkin-Wilf Sequence. The first $32$ elements are:

$$\frac{0}{1}, \frac{1}{1}, \frac{1}{2}, \frac{2}{1}, \frac{1}{3}, \frac{3}{2}, \frac{2}{3}, \frac{3}{1}, \frac{1}{4}, \frac{4}{3}, \frac{3}{5}, \frac{5}{2}, \frac{2}{5}, \frac{5}{3}, \frac{3}{4},$$
$$ \frac{4}{1}, \frac{1}{5}, \frac{5}{4}, \frac{4}{7}, \frac{7}{3}, \frac{3}{8}, \frac{8}{5}, \frac{5}{7}, \frac{7}{2}, \frac{2}{7}, \frac{7}{5}, \frac{5}{8}, \frac{8}{3}, \frac{3}{7}, \frac{7}{4}, \frac{4}{5}, \frac{5}{1}$$

|   Fraction    | Index | Binary  | Continued Fraction |
|---------------|-------|---------|--------------------|
| $\frac{0}{1}$ |   0   | 0b00000 | $[0]$              |
| $\frac{1}{1}$ |   1   | 0b00001 | $[1]$              |
| $\frac{1}{2}$ |   2   | 0b00010 | $[0; 1, 1]$        |
| $\frac{2}{1}$ |   3   | 0b00011 | $[2]$              |
| $\frac{1}{3}$ |   4   | 0b00100 | $[0; 2, 1]$        |
| $\frac{3}{2}$ |   5   | 0b00101 | $[1; 1, 1]$        |
| $\frac{2}{3}$ |   6   | 0b00110 | $[0; 1, 2]$        |
| $\frac{3}{1}$ |   7   | 0b00111 | $[3]$              |
| $\frac{1}{4}$ |   8   | 0b01000 | $[0; 3, 1]$        |
| $\frac{4}{3}$ |   9   | 0b01001 | $[1; 2, 1]$        |
| $\frac{3}{5}$ |  10   | 0b01010 | $[0; 1, 1, 1, 1]$  |
| $\frac{5}{2}$ |  11   | 0b01011 | $[2; 1, 1]$        |
| $\frac{2}{5}$ |  12   | 0b01100 | $[0; 2, 2]$        |
| $\frac{5}{3}$ |  13   | 0b01101 | $[1; 1, 2]$        |
| $\frac{3}{4}$ |  14   | 0b01110 | $[0; 1, 3]$        |
| $\frac{4}{1}$ |  15   | 0b01111 | $[4]$              |
| $\frac{1}{5}$ |  16   | 0b10000 | $[0; 4, 1]$        |
| $\frac{5}{4}$ |  17   | 0b10001 | $[1; 3, 1]$        |
| $\frac{4}{7}$ |  18   | 0b10010 | $[0; 1, 1, 2, 1]$  |
| $\frac{7}{3}$ |  19   | 0b10011 | $[2; 2, 1]$        | 
| $\frac{3}{8}$ |  20   | 0b10100 | $[0; 2, 1, 1, 1]$  |
| $\frac{8}{5}$ |  21   | 0b10101 | $[1; 1, 1, 1, 1]$  |
| $\frac{5}{7}$ |  22   | 0b10110 | $[0; 1, 2, 1, 1]$  |
| $\frac{7}{2}$ |  23   | 0b10111 | $[3; 1, 1]$        |
| $\frac{2}{7}$ |  24   | 0b11000 | $[0; 3, 2]$        |
| $\frac{7}{5}$ |  25   | 0b11001 | $[1; 2, 2]$        |
| $\frac{5}{8}$ |  26   | 0b11010 | $[0; 1, 1, 1, 2]$  |
| $\frac{8}{3}$ |  27   | 0b11011 | $[2; 1, 2]$        |
| $\frac{3}{7}$ |  28   | 0b11100 | $[0; 2, 3]$        |
| $\frac{7}{4}$ |  29   | 0b11101 | $[1; 1, 3]$        |
| $\frac{4}{5}$ |  30   | 0b11110 | $[0; 1, 4]$        |
| $\frac{5}{1}$ |  31   | 0b11111 | $[5]$              |

[^1]: https://en.wikipedia.org/wiki/Calkin%E2%80%93Wilf_tree#Breadth_first_traversal
[^2]: https://www.cs.utexas.edu/~EWD/ewd05xx/EWD578.PDF