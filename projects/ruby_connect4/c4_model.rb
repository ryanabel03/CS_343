class C4Model

  #Create the board
  def initialize(rows, columns, win_length)
    @board = []
    @length_to_win = win_length
    @columns = columns

    (1..rows).each do |row|
      @board << Array.new(columns)
    end
  end

  def board
    @board
  end

  def place_token(column, player)
    @board.reverse.each do |row|
      if row[column].nil?
        row[column] = player
        return "Placed #{player} in Column #{column}"
      end
    end
    raise "That column is full"
  end

  def check_rows(player)
    count = 0
    @board.each do |row|
      row.each do |element|
        element == player ? count += 1 : count = 0
        if count == @length_to_win
          return true
        end
      end
    end
    return false
  end

  def all_columns
    arr = []
    (0..@columns - 1).each do |column|
      sub_arr = []
      @board.reverse.each do |row|
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

  def check_forward_diagonal(player)
    (0..@columns - 1).each do |column|
      count = 0
      @board.each_with_index do |row, index|
        row[column] == @board[index + 1][column + 1] && !row[column].nil? ? count += 1 : count = 1

        if count == @length_to_win
          return true
        end
      end
    end
    return false
  end

  def check_backward_diagonal(player)
  end

  def check_columns(player)
    count = 0
    (0..@columns - 1).each do |column|
      @board.each do |row|
        row[column] == player ? count += 1 : count = 0

        if count == @length_to_win
          return true
        end
      end
    end
    return false
  end

  def who_won
    # if check_rows(1) || check_columns(1) || check_diagonals(1)
    #   return 1
    # else if check_rows(0) || check_columns(0) || check_diagonals(0)
    #   return 0
    # else
    #   return nil
    # end
  end
end
