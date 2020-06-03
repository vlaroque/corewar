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



turn_per_second = 1
turn = 0
turn_carry = 0                              #base25
pause = false
reset_screen
system("stty raw -echo")
square(1, 68, 1, 197, "white")
while true do

  key = pressed_char
  if key == "c"
    system("stty -raw echo")
    exit
  elsif key == "p"
    pause = pause ? false : true
  elsif key == "w"
    turn_per_second += 1
  elsif key == "r"
    turn_per_second -= 1
  end

  print_pos(3, 4, `./corewar -v -dump #{turn} ressources/champs/Gagnant.cor`)

  if pause == false
    turn_carry += turn_per_second
    if turn_carry >= 25
      turn += turn_carry / 25
      turn_carry = turn_carry % 25
    end
  end
  
  move_to 69, 100
  print ("c = exit | q = +10 | w = +1 | e = -10 | r = -1        actual = " + turn_per_second.to_s + " tps | turn " + turn.to_s + "                             " )
  sleep(0.04)
end


