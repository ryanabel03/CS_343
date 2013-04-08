(load "connect4_engine.lsp")

;; play the indicated sequence of moves, then verify that each move but the last results in no winner.
;; the last move should result in a winner being the player who made the last move.
(defun test-game (name board win-length moves)
 (let ((player 0)
       (result nil))
  (setf result (mapcar (lambda (move)
                        (place-token player move board)
                        (setf player (mod (+ player 1) 2))
                        (who-won win-length board))
                moves))
  (if (and (remove-duplicates (butlast result)) (first (last result)) (= (first (last result)) (mod (+ 1 (length moves)) 2)))
   (progn (format t "PASS! ~A ~%" name) t)
   (progn (format t "FAIL! ~A ~%" name) nil)
   )
  ))

;; Run an entire list of tests and report which pass and which fail
(defun run-tests (list)
 (let ((results (mapcar (lambda (params)
                         (test-game
                          (nth 0 params)
                          (make-board (nth 1 params) (nth 2 params))
                          (nth 3 params)
                          (nth 4 params))) list)))
  (format t "~A pass and ~A fail" (count t results) (count nil results))
  ))


;; The tests.  Add your own here.
 (run-tests '(("row 0" 7 7 4 (1 1 2 2 3 3 4))
              ("row 0 length 5" 7 7 5 (1 1 2 2 3 3 4 4 5))
              ("column 0" 7 7 4 (0 1 0 1 0 1 0))
              ("forward diagonal at mid" 7 7 4 (0 0 0 0 2 2 2 1 1 1 1 3))
              ("backward diagonal below mid" 5 5 3 (0 0 0 1 1 1 2))
              ("backward diagonal at mid" 5 5 5 (0 1 1 2 2 3 2 4 3 3 3 4 4 4 4))
              ("backward diagonal above mid" 4 4 3 (1 1 1 1 2 3 2 3 2))
              ("forward diagonal above mid" 4 4 3 (0 0 1 1 3 1 3 2 2 3 2 2))
              ("forward diagonal below mid" 4 4 3 (0 2 1 3 2 3 3))
              ))
