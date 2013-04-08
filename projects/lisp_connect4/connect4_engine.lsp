(defun intlist (a)
  (if (= a 1)
    '(1)
    (cons a (intlist(- a 1)))))

; Initialize an empty board of size rows X columns
(defun make-board (rows columns)
  (mapcar (lambda (blah) (make-list columns :initial-e  lement nil)) (intlist rows)))

(defun place-token (player column matrix)
  (if (null (nth column (nth (- (length (first matrix)) 1) matrix))) ; Is the element in the column of the last row null?
    (setf (nth column (nth (- (length (first matrix)) 1) matrix)) player); Set the column to the current player
    (place-token-recur player column (- (length (first matrix)) 2) matrix)); Go to the next row up 
  matrix)

(defun place-token-recur (player column row matrix)
  (if (null (nth column (nth row matrix)))  ;Is the element in (row, col) null
    (setf (nth column (nth row matrix)) player); Set it to player 
    (if (> row 0); base case 
      (place-token-recur player column (- row 1) matrix); Move up a row
      nil))); It is full

(defun check-rows(length-to-win player matrix)
  (some #'(lambda (n) (= length-to-win n)) (mapcar (lambda (row) (count player row)) matrix)))

(defun check-columns(length-to-win player matrix)
  (some #'(lambda (n) (= length-to-win n)) (mapcar (lambda (column) (count player column)) (all-columns matrix))))

;Get column colnum from a matrix
(defun get-column (colnum matrix)
  (mapcar (lambda (row) (nth colnum row)) matrix))

(defun item (row column matrix)
  (nth column (nth row matrix)))

(defun get-diagonal (row column matrix)
  (if (>= row (length matrix))
    nil
    (append (list (item row column matrix)) (get-diagonal (+ 1 row) (+ 1 column) matrix))))

(defun all-lower-back-diagonals (row column matrix)
  (if (>= row (length matrix))
    nil
    (append (list (get-diagonal row column matrix)) (all-lower-back-diagonals (+ 1 row) column matrix))))

(defun diagonals-for-column (col matrix)
  (let ((column col))
    (mapcar (lambda (row) (setq column (+ 1 column)) (nth column row)) matrix)))

(defun all-higher-back-diagonals (matrix)
  (map-with-index (lambda (row index) (diagonals-for-column (- index 1) matrix)) matrix))

(defun diagonals-for-forward-column (col matrix)
  (let ((column col))
    (mapcar (lambda (row) (setq column (- column 1)) (if (>= column 0) (nth column row) nil)) matrix)))

(defun all-higher-forward-diagonals (matrix)
  (let ((i (+ (length matrix) 1)))
  (map-with-index (lambda (row index) (setq i (- i 1)) (diagonals-for-forward-column i matrix)) matrix)))

(defun get-diagonal-too (row column matrix)
  (if (>= row (length matrix))
    nil
    (append (list (item row column matrix)) (get-diagonal-too (+ 1 row) (- column 1) matrix))))

(defun all-lower-forward-diagonals (row column matrix)
  (if (>= row (length matrix))
    nil
    (append (list (get-diagonal-too row column matrix)) (all-lower-forward-diagonals (+ 1 row) column matrix))))

(defun all-diagonals (matrix)
  (append (all-lower-forward-diagonals 0 (length (first matrix)) matrix)
          (all-higher-forward-diagonals matrix)
          (all-lower-back-diagonals 0 0 matrix)
          (all-higher-back-diagonals matrix)))

(defun who-won (win-length matrix)
  (cond 
    ((check-rows win-length 0 (all-diagonals matrix)) 0)
    ((check-rows win-length 1 (all-diagonals matrix)) 1)
    ((check-rows win-length 0 matrix) 0)
    ((check-rows win-length 1 matrix) 1)
    ((check-columns win-length 0 matrix) 0)
    ((check-columns win-length 1 matrix) 1)
    ))

;; This behaves like map, but also passes the index of the current
;; element This version of map is useful for some of the methods
;; below.  (Notice that it is written to be tail-recursive.)
(defun map-with-index (f list &optional head i)
 (let ((i (if i i 0))) ; set i to 0 if i is nil
   (if list 
       (map-with-index 
	f 
	(rest list) 
	(cons (funcall f (first list)  i) head) 
	(+ 1 i))
     (reverse head))))

;get all columns
(defun all-columns
  (matrix)
  (map-with-index 
   (lambda (column-value column-number) (get-column column-number matrix)) 
   (first matrix)))
