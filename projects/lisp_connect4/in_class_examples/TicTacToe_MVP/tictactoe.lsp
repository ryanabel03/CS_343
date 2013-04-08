 ; if all items in the array are the same, return that value, 
; otherwise, return nil
(defun all-same 
 (array)
 (if (eq 1 (length (remove-duplicates array))) 
     (first array)))

(defun ttt-win-row-only
  (matrix)
  (some 'identity (mapcar 'all-same matrix)))


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

; return the given column as an array
(defun get-column 
  (colnum matrix)
  (mapcar (lambda (row) (nth colnum row)) 
	  matrix))

; return a list of all columns
(defun all-columns
  (matrix)
  (map-with-index 
   (lambda (column-value column-number) (get-column column-number matrix)) 
   (first matrix)))

; find the nth item in the forward diagonal
(defun fd-item
  (index matrix) 
  (nth index (nth index matrix))
)

; find the nth item in the backward diagonal
(defun bd-item 
  (index matrix)
  (nth (- (length matrix) index 1) (nth index matrix))
)

; generate the specified diagonal
(defun diagonal
  (which matrix)
  (map-with-index 
   (lambda (row index) (funcall which index matrix)) 
   matrix))

(defun all-diagonals
  (matrix)
  (mapcar 
   (lambda (which) (diagonal which matrix)) 
   (list 'fd-item 'bd-item))
)

(defun ttt_win
  (matrix)
  (some 'identity
   (mapcar 'all-same
	   (apply 'append (mapcar 
			   (lambda (view) (funcall view matrix))
			   '(identity all-columns all-diagonals)
			   ))))
   ) ; End ttt_win

(setf matrix '((1 2 3 4) (5 6 7 8) (9 10 11 12) (13 14 15 16)))
(setf matrix2 '((1 2 3 4) (5 5 5 5) (9 10 11 12) (13 14 15 16)))
(setf matrix3 '((1 2 3 4) (5 6 3 8) (9 10 3 12) (13 14 3 16)))
(setf matrix4 '((1 2 3 4) (5 1 7 8) (9 10 1 12) (13 14 15 1)))
(setf matrix5 '((1 2 3 4) (5 6 4 8) (9 4 11 12) (4 14 15 16)))

(print (mapcar 'ttt_win (list matrix matrix2 matrix3 matrix4 matrix5)))
