import argparse
import csv
import matplotlib.pyplot as plt
from matplotlib import animation
import numpy as np

"""
Module to visualize boards and create
videos of game evolution
"""


class VisualizeConway:
    """
    Class used to visual Conway's Game of Life
    """

    def __init__(self, text_file: str) -> None:
        self.text_file = text_file
        self.rows = None
        self.cols = None
        self.generations = None
        self.game_history = {}
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(111)
        self.parse_header()  # Grab row, col, and generation from first line of file

    def parse_header(self):
        """
        Reads first line to get board rows, columns, 
        and number of generations
        """

        with open(self.text_file, "r") as f:
            reader = csv.reader(f)
            first_line = next(reader)
            self.rows, self.cols, self.generations = [int(x) for x in first_line]

        return None

    def load_game_history(self):
        """Reads in game file and loads into game history dictionary """

        if self.rows == 0 or self.cols == 0:
            self.parse_header()

        with open(self.text_file, "r") as f:
            reader = csv.reader(f)
            next(reader)  # Skip first line
            for row in reader:
                board = np.reshape(row[1:-1], (self.rows, self.cols))
                board_int = board.astype(np.int8)
                self.game_history[int(row[0])] = board_int
        return None

    def plot_board(self, generation: int, show_plot=True) -> None:
        """Plots board for a user specified generation"""

        self.ax.set_title(f"Generation: {generation}")
        self.ax.imshow(conway.game_history[generation], cmap="gray_r")
        self.ax.tick_params(
            left=False, bottom=False, labelleft=False, labelbottom=False
        )

        if show_plot:
            plt.tight_layout()
            plt.show()

        return None

    def save_image(self, file_name: str, **kwargs) -> None:
        """Save board as image"""

        plt.tight_layout()
        self.fig.savefig(file_name, **kwargs)

        return None

    def make_video(self, video_name: str = "conway_vid", fps: int = 15) -> None:
        """
        Creates video of game evolution

        Parameters
        ----------
            video_name : str
                Name of output video file
            fps : int
                Video frames per second

        Returns
        -------
            Video of game evolution
        """

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
        print(f"Video {video_name} saved!")

        return None


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("file", help="Text file containing history of game", type=str)
    parser.add_argument(
        "-o",
        "--output",
        help="Choose to save as image or video file",
        choices=["i", "img", "image", "v", "vid", "video"],
    )
    parser.add_argument(
        "-n",
        "--name",
        help="File name for image/ video",
        type=str,
        default="conway_game",
    )
    parser.add_argument(
        "-g",
        "--generation",
        help="Saves image of board at specified generation",
        type=int,
        default=1,
    )

    args = parser.parse_args()
    conway = VisualizeConway(args.file)
    conway.load_game_history()

    if args.output in {"i", "img", "image"}:
        conway.plot_board(args.generation, False)
        conway.save_image(args.name)
    elif args.output in {"v", "vid", "video"}:
        conway.make_video(args.name)
    else:
        print("Default to making image of initialized board....")
        conway.plot_board(1, False)
        conway.save_image("initial_board")
