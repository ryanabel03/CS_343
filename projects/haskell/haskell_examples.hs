module HaskellExamples where

  -- Recursive Palindrome
  is_palindrome x = | length x <= 1 = True
                      | head x == last x = is_palindrome_r . tail. init $ x
                      | otherwise = False


  -- Quadratic Roots Function
  functionRoot a b c = if d < 0 then error "0" else (x, y)
                          where
                            x = e + sqrt d / (2 * a)
                            y = e - sqrt d / (2 * a)
                            d = b * b - 4 * a * c
                            e = - b / (2 * a)

  -- Greatest Common Denominator Function
  greatestComDen x y =  greatestComDen' (abs x) (abs y) where
    greatestComDen' a 0  =  a
    greatestComDen' a b  =  greatestComDen' b (a `rem` b)


  -- Integer List function
  intList x = [1..x]


  -- Get all pythagorean triangles up to the "longest" length
  pythagTriples longest = [ (a,b,c) |
                  c <- [1..longest],
                  b <- [1..c],
                  a <- [1..b],
                  a^2 + b^2 == c^2 ]


  -- Rotate a list left
  rotate :: [a] -> Int -> [a]
  rotate [] _ = []
  rotate x 0 = x
  rotate x y
    | y > 0 = rotate (tail x ++ [head x]) (y-1)
    | otherwise = rotate (last x : init x) (y+1)


  -- Drop every N elements (take evens)
  dropEvery :: [a] -> Int -> [a]
  dropEvery list count = helper list count count
    where helper [] _ _ = []
          helper (x:xs) count 1 = helper xs count count
          helper (x:xs) count n = x : (helper xs count (n - 1))


  -- Flatten lists
  flatten :: NestedList a -> [a]
  flatten (Elem a   )   = [a]
  flatten (List (x:xs)) = flatten x ++ flatten (List xs)
  flatten (List [])     = []

  -- Taking advantage of the Maybe monad!
  divide :: (Fractional a) => a -> a -> Maybe a
  divide a 0 = Nothing
  divide a b = Just $ a / b

  -- Haskell I/O
  askForWords = do
  putStrLn "Please enter a word:"
  word <- getLine
  if word == ""
    then return []
    else do
      rest <- askForWords
      return (word : rest)