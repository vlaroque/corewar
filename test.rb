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
    print" "
  end
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
  print "\e[0m"
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

arg_str = ""
for arg in ARGV
  arg_str = arg_str + " " + arg
end


turn_per_second = 1
turn = 0
turn_carry = 0                              #base25
turn_save = -1
pause = false
reset_screen
system("stty raw -echo")
square(1, 68, 1, 198, "white")
square(1, 68, 2, 199, "white")
print_pos(3, 200, corewar)
puts `\e[?25l`
while true do

  key = pressed_char
  if key == "c"
    system("stty -raw echo")
	puts `\e[?25h`
    exit
  elsif key == " "
    pause = pause ? false : true
  elsif key == "K" and turn_per_second <= 990
    turn_per_second += 10
  elsif key == "k" and turn_per_second <= 999
    turn_per_second += 1
  elsif key == "J" and turn_per_second >= 10
    turn_per_second -= 10
  elsif key == "j" and turn_per_second >= 1
    turn_per_second -= 1
  elsif key == "h"
    turn -= 1
  elsif key == "H"
    turn -= 100
  elsif key == "l"
    turn += 1
  elsif key == "L"
    turn += 100
  end
  
  if turn != turn_save then
    mars = `./corewar -c -dump #{turn} #{arg_str}`
  end
  if mars[1] == 'n'
    pause = true
    print_pos(70, 100, mars)
  end
  print_pos(3, 4, mars)

  turn_save = turn

  if pause == false
    turn_carry += turn_per_second
    if turn_carry >= 25
      turn += turn_carry / 25
      turn_carry = turn_carry % 25
    end
  end
  
  move_to 69, 100
  print ("space = pause | c = exit | K = +10 | k = +1 | J = -10 | j = -1        actual = " + turn_per_second.to_s + " tps | turn " + turn.to_s + "                             " )
  sleep(0.04)
end


