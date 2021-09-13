# import argparse
import csv
import matplotlib.pyplot as plt
from matplotlib import animation
import numpy as np

"""
Module to visualize boards and create
board animations
"""


class VisualizeConway:
    """
    Class used to visual Conway's Game of Life
    """

    def __init__(self, text_file):
        self.text_file = text_file
        self.rows = 0
        self.cols = 0
        self.generations = 0
        self.game_history = {}
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(111)

    def parse_header(self):
        """
        Reads first line to get board rows, columns, 
        and number of generations
        """
        with open(self.text_file, "r") as f:
            reader = csv.reader(f)
            first_line = next(reader)
            self.rows, self.cols, self.generations = [int(x) for x in first_line]

    def load_game_history(self):
        """Reads in game file and loads into game history dictionary """
        if self.rows == 0 or self.cols == 0:
            self.parse_header()

        with open(self.text_file, "r") as f:
            reader = csv.reader(f)
            headers = next(reader)
            for row in reader:
                board = np.reshape(row[1:-1], (self.rows, self.cols))
                board_int = board.astype(np.int8)
                self.game_history[int(row[0])] = board_int
        return None

    def plot_board(self, generation):
        """Plots board"""
        self.ax.set_title(f"Generation: {generation}")
        self.ax.imshow(conway.game_history[generation], cmap="gray_r")
        self.ax.tick_params(
            left=False, bottom=False, labelleft=False, labelbottom=False
        )

        plt.tight_layout()
        plt.show()

        return None

    def save_image(self, file_name, **kwargs):
        """Save board as image"""
        plt.tight_layout()
        self.fig.savefig(file_name, **kwargs)

        return None

    def make_video(self, video_name="conway_vid", fps=15):
        """Creates video of game evolution"""
        frame_time = int(1 / fps * 1000)
        fig = plt.figure()
        ax = fig.add_subplot(111)
        ims = []

        print("Creating frames...")
        for i in range(1, self.generations):
            im = ax.imshow(conway.game_history[i], cmap="gray_r", animated=True)
            ax.tick_params(left=False, bottom=False, labelleft=False, labelbottom=False)
            plt.tight_layout()
            ims.append([im])

        print("Rendering video...")
        ani = animation.ArtistAnimation(
            fig, ims, interval=frame_time, repeat_delay=1000
        )

        ani.save(video_name + ".mp4")

        return None


if __name__ == "__main__":
    # TODO: Command line using argparse
    conway = VisualizeConway("game_out.txt")
    conway.load_game_history()
    conway.make_video("conway_test")
