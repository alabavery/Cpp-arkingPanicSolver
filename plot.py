import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import matplotlib.lines as mlines
from matplotlib.collections import PatchCollection


def prepare_plot():
	"""
	# :rtype: None
	"""
	plt.close() # since we're going to be calling plot_lot() iteratively, close the last iteration before doing anything
	fig, ax = plt.subplots() # create a new figure and axis
	plt.axis([0, 6, 0, 6]) # set zoom/window of graph
	ax.set_axis_bgcolor('0.6') # color parking lot
	plt.gca().axes.xaxis.set_ticklabels([]) # remove xaxis labels
	plt.gca().axes.yaxis.set_ticklabels([]) # remove yaxis labels

	line = mlines.Line2D([6,6],[3,4],lw=15., alpha=0.8, color='yellow') # define a yellow line to indicate the exit
	ax.add_line(line) # add line to graph
	return ax





def parse_achievable_positions(achievable_positions_io):
	"""
	: type achievable_positions_io: io wrapepr for txt file
	: rtype: 3d list
	"""

	all_achievable_positions = []
	
	for vehicle in achievable_positions_io:
		this_vehicles_positions = []
		for position in vehicle.split('|'):
			this_position = []
			for character in position.split(" "):
				try:
					int(character)
				except ValueError:
					continue
				else:
					this_position.append(int(character))

			if len(this_position) > 0:
				this_vehicles_positions.append(this_position)

		all_achievable_positions.append(this_vehicles_positions)

	return all_achievable_positions




def parse_vehicle_indices(vehicle_indices_io):
	"""
	: type vehicle_indices_io: io wrapper for vehicle indices txt file
	: rtype (yield): generator generating 1D list of ints at each step
	"""
	i = 0
	for line in vehicle_indices_io:
		this_arrangement_indices = []
		for character in line:
			try:
				int(character)
			except ValueError:
				continue
			else:
				this_arrangement_indices.append(int(character))

		yield this_arrangement_indices



def get_vehicle_rectangle(vehicle_squares):
	"""
	: type vehicle_squares: 1-dimensional list of integers -> the position of the vehicle to plot
	: rtype: mpatches.Rectangle object
	"""
	board_switcher = [ [0,5], [1,5], [2,5], [3,5], [4,5], [5,5] # the bottom left coords of each square
					 ,[0,4], [1,4], [2,4], [3,4], [4,4], [5,4]
					 ,[0,3], [1,3], [2,3], [3,3], [4,3], [5,3]
					 ,[0,2], [1,2], [2,2], [3,2], [4,2], [5,2]
					 ,[0,1], [1,1], [2,1], [3,1], [4,1], [5,1]
					 ,[0,0], [1,0], [2,0], [3,0], [4,0], [5,0] ]

	if (vehicle_squares[-1] - vehicle_squares[0]) % 6 > 0:
		bottom_left_coords = board_switcher[vehicle_squares[0]]
		height, width = 1,len(vehicle_squares)

	else:
		bottom_left_coords = board_switcher[vehicle_squares[-1]]
		height, width = len(vehicle_squares), 1

	return mpatches.Rectangle(bottom_left_coords, width, height)
	



def plot_lot(achievable_positions, position_indices):
	"""
	: type achievable_positions: 3d int list
	: type position_indices: 1d list of ints
	: rtype: None
	"""
	plt.close()
	ax = prepare_plot()

	patches = []
	for vehicle_index, position_index in enumerate(position_indices):	
		patches.append(get_vehicle_rectangle(achievable_positions[vehicle_index][position_index]))
		print(vehicle_index, position_index)
	
	collection = PatchCollection(patches, alpha=0.3, match_original=True)
	ax.add_collection(collection)
	plt.pause(0.5)





achievable_positions_io = open('achievablePositionsWriteFile.txt', 'r')
achievable_positions = parse_achievable_positions(achievable_positions_io)
achievable_positions_io.close()

vehicle_indices_io = open('arrangementSequenceWriteFile.txt')
indices_generator = parse_vehicle_indices(vehicle_indices_io)
for indices in indices_generator:
	plot_lot(achievable_positions, indices)

vehicle_indices_io.close()

