require_relative 'c4_model.rb'
describe C4Model do

  def place_at_location(board, row, column, player)
    board[row][column] = player
  end

  describe "#initialize" do
    def all_empty?(board)
      board.flatten.map do |elem|
        if !elem.nil?
          return false
        end
      end
      return true
    end

    it "creates a new empty board of varied sizes" do
      engine = C4Model.new 7, 6, 3

      engine.board.size.should == 7
      engine.board[0].size.should == 6
      all_empty?(engine.board).should be_true

      # No longer empty
      place_at_location(engine.board, 1, 1, 1)
      all_empty?(engine.board).should be_false
    end
  end

  describe "#place_token" do
    it "places a token in the first nil column" do
      engine = C4Model.new 4, 4, 3

      engine.place_token 1

      engine.board[3][1].should == 0

      engine.place_token 1

      engine.board[3][1].should == 0
      engine.board[2][1].should == 1
    end

    it "throws an exception if the column is full" do
      engine = C4Model.new 4, 4, 3
      (0..3).each do |a|
        engine.place_token 1
      end
      
      engine.place_token(1).should be_nil
    end
  end

  describe "#check_rows" do
    it "Resets count correctly" do
      engine = C4Model.new 7, 7, 3

      board = 
        [
          [0, 0, 1, 0, 0, 1, 0]
        ]

      engine.check_rows(1, board).should be_false

      board << [1, 1, nil, 1, 1, 1, 0]

      engine.check_rows(1, board).should be_true
    end

    it "can find a winner on the top row" do
      engine = C4Model.new 3, 3, 3

      board = 
        [
          [1, 1, 1],
          [nil, nil, nil],
          [nil, nil, nil]
        ]

      engine.check_rows(1, board).should be_true
    end

    it "can find a winner in the middle" do
      engine = C4Model.new 4, 4, 3

      board = 
        [
          [nil, nil, nil, 1],
          [1, 1, 1, 0],
          [nil, nil, nil, nil]
        ]

      engine.check_rows(1, board).should be_true
    end
  end


  describe "#check_columns" do
    it "resets count correctly" do
      engine = C4Model.new 4, 4, 3

      board =
        [
          [0, nil, nil, nil],
          [0, nil, nil, nil],
          [1, nil, nil, nil],
          [0, nil, nil, nil]
        ]

      engine.check_columns(0, board).should be_false
    end

    it "works for the right edge column" do
      engine = C4Model.new 4, 4, 3

      board = 
        [
          [nil, nil, nil, 0],
          [nil, nil, nil, 0],
          [nil, nil, nil, 0]
        ]
      engine.check_columns(0, board).should be_true
    end
  end

  describe "#forward_diagonals" do
    it "gets main forward diagonals" do
      engine = C4Model.new 3, 3, 3

      place_at_location(engine.board, 2, 0, 1)
      place_at_location(engine.board, 1, 1, 0)
      place_at_location(engine.board, 0, 2, 1)

      result = engine.forward_diagonals

      result.include?([1, 0, 1]).should be_true
    end

    it "gets forward diagonals below main" do
      engine = C4Model.new 3, 3, 3

      place_at_location(engine.board, 2, 1, 1)
      place_at_location(engine.board, 1, 2, 0)

      result = engine.forward_diagonals

      result.include?([1, 0, nil]).should be_true
    end

    it "gets forward diagonals above main" do
      engine = C4Model.new 3, 3, 3

      place_at_location(engine.board, 1, 0, 0)
      place_at_location(engine.board, 0, 1, 0)

      result = engine.forward_diagonals

      result.include?([0, 0, nil]).should be_true
    end

    it "check all the things" do
      engine = C4Model.new 4, 4, 3

      #First column
      place_at_location(engine.board, 3, 0, 1)
      place_at_location(engine.board, 2, 0, 0)
      place_at_location(engine.board, 1, 0, 1)
      place_at_location(engine.board, 0, 0, nil)

      #Second column 
      place_at_location(engine.board, 3, 1, 0)
      place_at_location(engine.board, 2, 1, 1)
      place_at_location(engine.board, 1, 1, 1)

      #Third column
      place_at_location(engine.board, 3, 2, 1)
      place_at_location(engine.board, 2, 2, 0)
      place_at_location(engine.board, 1, 2, 1)

      #Fourth column
      place_at_location(engine.board, 3, 3, 0)
      place_at_location(engine.board, 2, 3, 0)
      place_at_location(engine.board, 1, 3, 0)
      place_at_location(engine.board, 0, 3, 1)

      expected = [[1, 1, 1, 1], [0, 0, 0, nil], [1, 0, nil, nil,], [0, nil, nil, nil],
                  [1, 1, 1, 1], [0, 1, nil, nil], [1, nil, nil, nil], [nil, nil, nil, nil]]


      result = engine.forward_diagonals
      result.should == expected
    end
  end
  
  describe "#all_columns" do
    it "returns all the columns" do
      engine = C4Model.new 3, 3, 3

      board = 
        [
          [nil, nil, nil],
          [1, 1, nil],
          [1, 0, nil]
        ]

      expected = [[1, 1, nil], [0, 1, nil], [nil, nil, nil]]

      engine.all_columns(board).should == expected
    end
  end

  describe "#check_forward_diagonal" do
    it "can find a win on the main diagonal" do
      engine = C4Model.new 4, 4, 4


      place_at_location(engine.board, 3, 0, 1)
      place_at_location(engine.board, 2, 1, 1)

      engine.check_forward_diagonal(1).should be_false

      place_at_location(engine.board, 1, 2, 1)
      place_at_location(engine.board, 0, 3, 1)

      engine.check_forward_diagonal(1).should be_true
    end
  end

  describe "#backward_diagonals" do
    it "can get a backward diagonal on the main line" do
      engine = C4Model.new 3, 3, 4

      place_at_location(engine.board, 0, 0, 1)
      place_at_location(engine.board, 1, 1, 1)
      place_at_location(engine.board, 2, 2, 0)

      result = engine.backward_diagonals

      result.include?([1, 1, 0]).should be_true
    end

    it "can get a backward diagonal above the main line" do
      engine = C4Model.new 3, 3, 4

      place_at_location(engine.board, 0, 2, 1)
      place_at_location(engine.board, 1, 3, 0)

      result = engine.backward_diagonals

      result.include?([1, 0, nil]).should be_true
    end

    it "can get a backward diagonal below the main line" do
      engine = C4Model.new 3, 3, 4

      place_at_location(engine.board, 1, 0, 1)
      place_at_location(engine.board, 2, 1, 0)

      result = engine.backward_diagonals

      result.include?([1, 0, nil]).should be_true
    end

    it "can put it all together" do
      engine = C4Model.new 4, 4, 3

      board = 
        [
          [0, 1, 1, 1],
          [1, 0, 0, 1],
          [0, 0, 0, 1],
          [1, 1, 0, 0]
        ]

        result = engine.backward_diagonals(board)

        expected = [[0, 0, 0, 0], [1, 0, 1, nil], [1, 1, nil, nil], [1, nil, nil, nil],
                    [1, nil, nil, nil], [0, 1, nil, nil], [1, 0, 0, nil], [0, 0, 0, 0]]

        result.should == expected
    end
  end

  def make(rows=7, cols=7, win_length=4)
    C4Model.new(rows, cols, win_length)
  end

  describe 'place_token' do
    it 'returns nil if column is too high' do
      make(7, 6).place_token(6).should be nil
    end

    it 'returns nil if the column is full' do 
      size = 5
      board = make(size)
      (1..size).each do |i| 
        board.place_token(size - 1).should_not be_nil
      end
      board.place_token(size -1).should be_nil
    end
  end

  def verify_moves(board, moves)
    last_move = moves.pop
    moves.each do |move|
      board.place_token(move).should_not be_nil
      board.who_won.should be_nil
    end
    board.place_token(last_move).should_not be_nil
    board.who_won.should == (moves.length % 2)
  end


  it 'recognizes a win in bottom row'  do
    verify_moves(make, [1, 1, 2, 2, 3, 3, 4]) 
  end
    
  it 'recognizes a win in the first column' do
    verify_moves(make, [0, 1, 0, 1, 0, 1, 0])
  end

  it 'recognizes a diagonal win' do
    verify_moves(make, [0, 0, 0, 0, 2, 2, 2, 1, 1, 1, 1, 3])
  end
end # describe
