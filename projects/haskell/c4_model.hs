module Model where
  import qualified Data.Sequence as Seq

  makeBoard rows columns = replicate rows (replicate columns (-1))

  placeToken player column matrix =
    if last(matrix)!!column == -1
      then Seq.update 1 1 (Seq.fromList(last(matrix)))
      else
