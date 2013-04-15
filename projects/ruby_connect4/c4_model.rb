class C4Model

  #Create the board
  def initialize(rows, columns, win_length)
    @board = []
    @length_to_win = win_length
    @columns = columns
    @player = 0

    (1..rows).each do |row|
      @board << Array.new(columns)
    end
  end

  def board
    @board
  end

  def columns
    @columns
  end

  def player
    @player
  end

  def increment_turn
    @player += 1
    @player = @player % 2
  end

  def place_token(column)
    if column > @columns - 1 || column < 0
      return nil
    end

    @board.reverse.each do |row|
      if row[column].nil?
        row[column] = @player
        increment_turn
        return true
      end
    end
    return nil
  end

  def check_rows(player, board=nil)
    board ||= @board
    board.each do |row|
      count = 0
      row.each do |element|
        element == player ? count += 1 : count = 0
        if count == @length_to_win
          return true
        end
      end
    end
    return false
  end

  def all_columns(board=nil)
    board ||= @board
    arr = []
    (0..@columns - 1).each do |column|
      sub_arr = []
      board.reverse.each do |row|
        sub_arr << row[column]
      end
      arr << sub_arr
    end
    arr
  end

  def forward_diagonals
    arr = []

    # At & Below Diagonal
    (0..@columns - 1).each do |offset|
      sub_arr = []
      @board.reverse.each_with_index do |row, index|
        sub_arr << row[index + offset]
      end
      arr << sub_arr
    end

    (0..@board.size - 1).each do |offset|
      sub_arr = []
      all_columns.each_with_index do |column, index|
        sub_arr << column[index + offset]
      end
      arr << sub_arr
    end
    arr
  end

  def backward_diagonals(board=nil)
    arr = []
    board ||= @board

    # At & Above Diagonal
    (0..@columns - 1).each do |offset|
      sub_arr = []
      board.each_with_index do |row, index|
        sub_arr << row[index + offset]
      end
      arr << sub_arr
    end

    # At & Below Diagonal
    (0..@columns - 1).each do |offset|
      sub_arr = []
      all_columns(board).each_with_index do |column, index|
        if offset - index < 0
          sub_arr << nil
        else
          sub_arr << column[offset - index]
        end
      end
      arr << sub_arr
    end
    arr
  end

  def check_forward_diagonal(player)
    check_rows(player, forward_diagonals)
  end

  def check_backward_diagonal(player)
    check_rows(player, backward_diagonals)
  end

  def check_diagonals(player)
    check_forward_diagonal(player) || check_backward_diagonal(player) ? true : false
  end

  def check_columns(player, board=nil)
    board ||= @board
    (0..@columns - 1).each do |column|
      count = 0
      board.each do |row|
        row[column] == player ? count += 1 : count = 0

        if count == @length_to_win
          return true
        end
      end
    end
    return false
  end

  def who_won
    if check_rows(1) || check_columns(1) || check_diagonals(1)
      return 1
    elsif check_rows(0) || check_columns(0) || check_diagonals(0)
      return 0
    else
      return nil
    end
  end

  def print_board
    @board.each do |row|
      row.each do |element|
        if element
          print " #{element} |"
        else
          print "   |"
        end
      end
      puts
    end
  end
end
