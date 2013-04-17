(load "connect4_engine.lsp")

(defun collist(a)
  (if (= a 1)
    '(0)
    (cons (- a 1) (collist(- a 1)))))

(defun print-columns (board)
  (mapcar (lambda (colnum) (format t " ~3A" colnum)) (reverse (collist (length (first board)))))
  (format t "~%"))

(defun print-board (board)
  (mapcar (lambda (rows) (mapcar (lambda (element) (if (null element) (format t "   |")  (format t "~3A|" element))) rows) (format t "~%")) board)
  (print-columns board))

(defun get-next-move (player numcols matrix)
  (let ((column nil))
    (format t "Player ~A's Turn." player) 
    (print "Drop token in column: ")
    (setf column (read))
    (cond 
      ((equal column 'QUIT) nil)
      ((not (integerp column))
       (progn
         (format t "Please enter an integer.")
         (get-next-move player numcols matrix)))
      ((or (< column 0) (> column numcols))
       (progn
         (format t "Please enter an integer between 0 and ~A" numcols)
         (get-next-move player numcols matrix)))) column))

(defun increment-turn (turn)
  (mod (+ turn 1) 2))

(defun parse-item (question)
  (let ((item nil))
    (print question)
    (setf item (read))
    (cond
      ((equal item 'QUIT) nil)
      ((not (integerp item))
       (progn
         (format t "Please enter an integer.")
         (parse-item question)))
      ((< item 0)
       (progn
         (format t "Please enter an integer above 0")))) item))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; main
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(setf win-length (parse-item "How many consecutive numbers for a win?"))
(setf numcols (parse-item "How many Columns?"))
(setf numrows (parse-item "How many Rows?"))


(setf board (make-board numrows numcols))
(setf player -1)

(loop
  (setf player (increment-turn player))
  (print-board board)
  (let ((next-token (get-next-move player 7 board)))
    (when (equal next-token nil)
      (return "Quit!"))
      (progn
        (setq board (place-token player next-token board))
        (if (not (equal (who-won win-length board) nil))
          (progn
            (print-board board)
            (format t "Player ~A Wins!~%" (who-won win-length board))
            (return))
          -1)
        )))
