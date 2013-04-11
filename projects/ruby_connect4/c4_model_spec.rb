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
      engine.place_token(1, 1)
      all_empty?(engine.board).should be_false
    end
  end

  describe "#place_token" do
    it "places a token in the first nil column" do
      engine = C4Model.new 4, 4, 3

      engine.place_token(1, 1)

      engine.board[3][1].should == 1

      engine.place_token(1, 1)

      engine.board[3][1].should == 1
      engine.board[2][1].should == 1
    end

    it "throws an exception if the column is full" do
      engine = C4Model.new 4, 4, 3
      (0..3).each do |a|
        engine.place_token(1, 1)
      end
      
      expect { engine.place_token(1,1) }.to raise_error
    end
  end

  describe "#check_rows" do
    it "Resets count correctly" do
      engine = C4Model.new 7, 7, 3

      engine.place_token(0, 1)
      engine.place_token(1, 1)
      engine.place_token(2, 0)

      # Count should be reset
      engine.check_rows(1).should be_false

      engine.place_token(3, 1)
      engine.place_token(4, 1)
      engine.place_token(5, 1)

      engine.check_rows(1).should be_true
    end

    it "can find a winner on the top row" do
      engine = C4Model.new 3, 3, 3

      #First row
      engine.place_token(0, 0)
      engine.place_token(0, 0)
      engine.place_token(0, 1)

      #Second row
      engine.place_token(1, 0)
      engine.place_token(1, 0)
      engine.place_token(1, 1)

      #Third row
      engine.place_token(2, 0)
      engine.place_token(2, 0)
      engine.place_token(2, 1)

      engine.check_rows(1).should be_true
    end

    it "can find a winner in the middle" do
      engine = C4Model.new 4, 4, 3

      #First row
      engine.place_token(0, 0)
      engine.place_token(0, 0)
      engine.place_token(0, 1)
      engine.place_token(0, 0)

      #Second row
      engine.place_token(1, 0)
      engine.place_token(1, 0)
      engine.place_token(1, 1)
      engine.place_token(1, 0)

      #Third row
      engine.place_token(2, 0)
      engine.place_token(2, 0)
      engine.place_token(2, 1)
      engine.place_token(2, 0)

      engine.check_rows(1).should be_true
    end
  end


  describe "#check_columns" do
    it "resets count correctly" do
      engine = C4Model.new 4, 4, 3

      engine.place_token(0, 0)
      engine.place_token(0, 0)
      engine.place_token(0, 1)
      engine.place_token(0, 0)

      engine.check_columns(0).should be_false

      engine.place_token(3, 0)
      engine.place_token(3, 0)
      engine.place_token(3, 0)

      engine.check_columns(0).should be_true
    end

    it "works for the right edge column" do
      engine = C4Model.new 4, 4, 3

      engine.place_token(3, 1)
      engine.place_token(3, 1)
      engine.place_token(3, 1)

      engine.check_columns(1).should be_true
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
      puts result.inspect

      result.include?([0, 0, nil]).should be_true
    end

    it "check all the things" do
      engine = C4Model.new 4, 4, 3

    end
  end
  
  describe "#all_columns" do
    it "returns all the columns" do
      engine = C4Model.new 3, 3, 3

      engine.place_token(0, 1)
      engine.place_token(0, 1)
      engine.place_token(1, 0)
      engine.place_token(1, 1)

      expected = [[1, 1, nil], [0, 1, nil], [nil, nil, nil]]

      engine.all_columns.should == expected
    end
  end
end

#   describe "#check_forward_diagonal" do
#     it "can find a win on the main diagonal" do
#       engine = C4Model.new 4, 4, 4
# 
# 
#       place_at_location(engine.board, 3, 0, 1)
#       place_at_location(engine.board, 2, 1, 1)
#       place_at_location(engine.board, 1, 2, 1)
#       place_at_location(engine.board, 0, 3, 1)
# 
#       puts engine.board.inspect
# 
#       engine.check_forward_diagonal(1).should be_true
#     end
#   end
# end

# describe C4Model do
# 
#   def make(rows=7, cols=7, win_length=4)
#     C4Model.new(rows, cols, win_length)
#   end
# 
#   describe 'place_token' do
#     it 'returns nil if column is too high' do
#       make(7, 6).place_token(6).should be nil
#     end
# 
#     it 'returns nil if the column is full' do 
#       size = 5
#       board = make(size)
#       (1..size).each do |i| 
#         board.place_token(size - 1).should_not be_nil
#       end
#       board.place_token(size -1).should be_nil
#     end
# 
#     # add other place_token tests here
# 
#   end # place_token
# 
#   def verify_moves(board, moves)
#     last_move = moves.pop
#     moves.each do |move|
#       board.place_token(move).should_not be_nil
#       board.who_won.should be_nil
#     end
#     board.place_token(last_move).should_not be_nil
#     board.who_won.should == (moves.length % 2)
#   end
# 
# 
#   # it 'recognizes a win in bottom row'  do
#   #   verify_moves(make, [1, 1, 2, 2, 3, 3, 4]) 
#   # end
#   #   
#   # it 'recognizes a win in the first column' do
#   #   verify_moves(make, [0, 1, 0, 1, 0, 1, 0])
#   # end
# 
#   # it 'recognizes a diagonal win' do
#   #   verify_moves(make, [0, 0, 0, 0, 2, 2, 2, 1, 1, 1, 1, 3])
#   # end
# 
# end # describe
