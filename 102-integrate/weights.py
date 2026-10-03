import numpy as np
import sympy as sp

n = 5
digits = 32
x = sp.Symbol('x', real=True)
polinoms = [sp.Integer(1), x]
for i in range(1, n):
    polinoms.append(
        ((2*i + 1) * x * polinoms[i] - i * polinoms[i-1]) / (i + 1)
    )

print(f"\n Полимномы Лежандра:")
for k, P in enumerate(polinoms):
    print(f"P{k} = {sp.expand(P)}")

nodes = sorted(sp.solve(polinoms[n], x), key=float)
nodes_float =[sp.N(r, digits) for r in nodes]

print(f"\nКорни полинома порядка n = {n}:", nodes_float)

weights = []
for i in range(0,n):
    p_down = sp.Integer(1)
    p_up = sp.Integer(1)
    for j in range(0,n):
        print(f"\rProcessing weights... i = {i}, j = {j}", end='', flush=True)
        if j != i:
            p_up = p_up * (x - nodes[j])
            p_down *= (nodes[i] - nodes[j])
    weights.append(sp.integrate(p_up/p_down, (x, -1, 1)))
    print(f"\nWeight {i} is done!")
weights_float = [sp.N(r, digits) for r in weights]
with open('weights.txt', 'w') as f:
    f.write(f"{n} {digits}\n")
    for i in range(n):
        f.write(str(nodes_float[i]) + ' ' + str(weights_float[i]) + "\n")

