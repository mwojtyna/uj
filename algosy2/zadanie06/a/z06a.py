import matplotlib.pyplot as plt

tour = [(0, 0), (1, 2), (0, 4), (1, 6), (3, 7), (5, 6), (7, 7), (6, 5), (5, 7), (7, 6), (6, 4), (7, 2), (6, 0), (4, 1), (2, 0), (0, 1), (1, 3), (0, 5), (1, 7), (3, 6), (1, 5), (0, 7), (2, 6), (4, 7), (6, 6), (7, 4), (6, 2), (7, 0), (5, 1), (3, 0), (1, 1), (0, 3), (2, 2), (1, 0), (0, 2), (1, 4), (0, 6), (2, 7), (4, 6), (6, 7), (7, 5), (6, 3), (7, 1), (5, 0), (3, 1), (2, 3), (3, 5), (4, 3), (5, 5), (3, 4), (4, 2), (6, 1), (5, 3), (4, 5), (2, 4), (3, 2), (4, 0), (2, 1), (3, 3), (2, 5), (4, 4), (5, 2), (7, 3), (5, 4)]


def plot_knight_tour(tour, board_size=None):
    xs = [c + 0.5 for _, c in tour]
    ys = [r + 0.5 for r, _ in tour]

    if board_size is None:
        board_size = max(max(r for r, _ in tour), max(c for _, c in tour)) + 1

    plt.figure(figsize=(6, 6))

    # grid
    for i in range(board_size + 1):
        plt.plot([0, board_size], [i, i], color="lightgray", linewidth=1)
        plt.plot([i, i], [0, board_size], color="lightgray", linewidth=1)

    # path
    plt.plot(xs, ys, marker="o", color="blue", linewidth=2)

    # step labels
    for i, (r, c) in enumerate(tour):
        plt.text(c + 0.5, r + 0.5, str(i), ha="center", va="center", fontsize=9)

    plt.gca().set_aspect("equal")
    plt.gca().invert_yaxis()
    plt.xticks(range(board_size + 1))
    plt.yticks(range(board_size + 1))
    plt.title("Knight Tour")
    plt.show()


plot_knight_tour(tour)
