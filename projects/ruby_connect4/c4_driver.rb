require_relative 'c4_model'

def parse_data(prompt, min)
  print prompt
  text = STDIN.gets
  data = text.to_i
  if data < min
    puts "Please enter a valid number (> #{min})"
    parse_data prompt
  end
  data
end

def read_rows
  parse_data "Enter number of Rows: ", 1
end

def read_cols
  parse_data "Enter number of Columns: ", 1
end

def read_win_length
  parse_data "Enter win length: ", 3
end

def next_move(engine)
  column = parse_data "Enter Column to Drop in: ", 0

  if column > engine.columns - 1
    puts "The number you entered exceeded the number of columns"
    engine.print_board
    next_move engine
  elsif !engine.place_token column
    puts "That column is full"
    engine.print_board
    next_move engine
  else
    engine.print_board
  end
end

def play_game(rows, columns, win_length)
  engine = C4Model.new rows, columns, win_length
  engine.print_board

  while(!engine.who_won)
    next_move engine
  end

  puts "Player #{(engine.player - 1) % 2} Won!"
end

rows = read_rows
columns = read_cols
win_length = read_win_length

play_game rows, columns, win_length
