from pyeda.inter import *

DIGITS = "123456789"

X = exprvars('x', (1, 10), (1, 10), (1,10))

V = And(*[
        And(*[
            OneHot(*[ X[r, c, v]
                for v in range(1, 10) ])
            for c in range(1, 10) ])
        for r in range(1, 10) ])


R = And(*[
        And(*[
            OneHot(*[ X[r, c, v]
                for c in range(1, 10) ])
            for v in range(1, 10) ])
        for r in range(1, 10) ])

C = And(*[
        And(*[
            OneHot(*[ X[r, c, v]
                for r in range(1, 10) ])
            for v in range(1, 10) ])
        for c in range(1, 10) ])

B = And(*[
        And(*[
            OneHot(*[ X[3*br+r, 3*bc+c, v]
                for r in range(1, 4) for c in range(1, 4) ])
            for v in range(1, 10) ])
        for br in range(3) for bc in range(3) ])

S = And(V, R, C, B)

grid1 = ( ".73|...|8.."
        "..4|13.|.5."
        ".85|..6|31."
        "---+---+---"
        "5..|.9.|.3."
        "..8|.1.|5.."
        ".1.|.6.|..7"
        "---+---+---"
        ".51|6..|28."
        ".4.|.52|9.."
        "..2|...|64." )

grid2 = ("6..|3.2|..."
        ".5.|...|.1."
        "...|...|..."
        "---+---+---"
        "7.2|6..|..."
        "...|...|.54"
        "3..|...|..."
        "---+---+---"
        ".8.|15.|..."
        "...|.4.|2.."
        "...|...|7.." )


def parse_grid(grid):
    chars = [c for c in grid if c in DIGITS or c in "0."]
    assert len(chars) == 9 ** 2
    return And(*[ X[i // 9 + 1, i % 9 + 1, int(c)]
        for i, c in enumerate(chars) if c in DIGITS ])


def get_val(point, r, c):
    for v in range(1, 10):
        if point[X[r, c, v]]:
            return DIGITS[v-1]
    return "X"

def display(point):
    chars = list()
    for r in range(1, 10):
        for c in range(1, 10):
            if c in (4, 7):
                chars.append("|")
            chars.append(get_val(point, r, c))
        if r != 9:
            chars.append("\n")
            if r in (3, 6):
                chars.append("---+---+---\n")
    print("".join(chars))

def solve(grid):
    with parse_grid(grid):
        return S.satisfy_one()


# display(solve(grid1))
display(solve(grid2))