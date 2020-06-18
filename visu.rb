require 'io/wait'

def reset_screen()
	print "\e[2J"
end

def move_to(row, colomn)
	print "\e[#{row};#{colomn}f"
end

def white_bg()
	print "\e[47m"
end

def print_x_space(x)
	x.times do
		print " "
	end
end

def reset_color()
	print "\e[0m"
end


def square(first_row, last_row, first_col, last_col, color)
	row = first_row
	move_to row, first_col
	white_bg
	print_x_space(last_col - first_col)
	while row < last_row
		move_to row, first_col
		print_x_space(1)
		move_to row, last_col
		print_x_space(1)
		row += 1
	end
	move_to last_row, first_col
	print_x_space(last_col - first_col + 1)
	reset_color
end

corewar = '
	_____    _____   __________   __________
   /  ___|  / ___ \  |_____    \  |________|
  |  /     |  | |  |  _____)    )   ______
  |  |     |  ( )  | |        _/    |____|
  |  \___  |  |_|  | |    |   \   __________
   \_____|  \_____/  |____|\___\  |________|
____      ____      ____  ____     __________
\   \    /    \    /   / /    \    |_____    \
 \   \  /      \  /   / /      \    _____)    )
  \   \/   /\   \/   / /   /\   \  |        _/
   \      /  \      / /    __    \ |    |   \
	\____/    \____/ /____/  \____\|____|\___\

' 
corewar2 = '
  ________  _________ __________   _________
 |    ____||   ___   |   ___    \ |_________|
 |   |     |   | |   |   ___)    )   _____
 |   |     |   ( )   |        __/   |_____|
 |   |____ |   |_|   |    |    \   _________
 |________||_________|____|\____\ |_________|
____      ____      ____ ____      __________
\   \    /    \    /   //    \    |______    \
 \   \  /      \  /   //      \    ______)    )
  \   \/   /\   \/   //   /\   \  |        __/
   \      /  \      //    __    \ |    |    \
	\____/    \____//____/  \____\|____|\____\

' 

ctrls = '
SPACE   >   Pause
h / H   >   - 1 / 100 Turns
l / L   >   + 1 / 100 Turns
j / J   >   - 1 / 10  Turns per second
k / K   >   + 1 / 10  Turns per second
c       >   Exit
'

def print_pos(row, col, str)
	str_arr = str.split("\n")
	for line in str_arr
		move_to row, col
		print line
		row += 1
	end
end

def pressed_char
	begin
		#    system("stty raw -echo")
		char = nil
		if $stdin.ready?
			char = $stdin.getc
		end
		if char
			char.chr
		end
	ensure
		#    system("stty -raw echo")
	end
end

def clean_exit
	system("stty -raw echo")
	print "\e[?25h"
	print "\n"
	exit
end

def key_to_action(key)
	if key == "c"
		clean_exit
	elsif key == " "
		$pause = $pause ? false : true
	elsif key == "K"
		$turn_per_second += 10
	elsif key == "k"
		$turn_per_second += 1
	elsif key == "J"
		$turn_per_second -= 10
	elsif key == "j"
		$turn_per_second -= 1
	elsif key == "h"
		$turn -= 1
	elsif key == "H"
		$turn -= 100
	elsif key == "l"
		$turn += 1
	elsif key == "L"
		$turn += 100
	end
end

def global_values_fix
	if $turn_per_second < 0
		$turn_per_second = 0;
	elsif $turn_per_second > 1000
		$turn_per_second = 1000 
	end
	if $turn < 0
		$turn = 0
	end
end

def truncate(str, len = 10)
	if str.length > len
		return "#{str[0...len]}...\n"
	else
		return str
	end
end

arg_str = ""
for arg in ARGV
	arg_str = arg_str + " " + arg
end


$turn_per_second = 1
$turn = 0

mars = `./corewar -c -dump #{$turn} #{arg_str}`
if mars.include? "Error"
	print mars
	clean_exit
end


turn_carry = 0                              #base25
turn_save = -1
$pause = false
reset_screen
system("stty raw -echo")
square(1, 68, 1, 198, "white")
square(1, 68, 2, 199, "white")
square(1, 68, 201, 260, "white")
print_pos(3, 205, corewar2)

champ_line = 40
champs = `./corewar -p #{arg_str}`
champs_array = champs.split("\n");
for line in champs_array
	print_pos(champ_line, 205, "#{truncate(line, 60)}")
	champ_line += 1;
end
reset_color

print_pos(55, 205, ctrls)
print "\e[?25l"

while true do

	key = pressed_char
	key_to_action(key)
	global_values_fix
	if $turn != turn_save then
		mars = `./corewar -c -dump #{$turn} #{arg_str}`
		print_pos(30, 205, "cycle : #{$turn.to_s}\nspeed : #{$turn_per_second.to_s}")
	end
	if mars[1] == 'o'
		print_pos(70, 100, mars)
		clean_exit
	end
	print_pos(3, 5, mars)
	reset_color
	turn_save = $turn
	if $pause == false
		turn_carry += $turn_per_second
		if turn_carry >= 25
			$turn += turn_carry / 25
			turn_carry = turn_carry % 25
		end
		print_pos(33, 205, "          ")
	elsif
		print_pos(33, 205, "PAUSE\n")
	end
	sleep(0.04/(1.0 + ($turn.to_f/4000.0)))
end
