;; example of how to nicely print out a list of numbers
(defun print-items (items)
 (mapcar (lambda (item) (format t "| ~A " item)) items)
 (format t "|~%"))


;; Prompt the user to enter an integer in the range [low, high],
;; or return nil if the user asks to quit.
;;
;; Notice that this function uses tail-recursion, which many LISP
;; compilers can optimize into a regular loop;
(defun enter-location (value low high)
 (let ((index nil))
  (format t "Please enter a location for value ~A: " value)
  (setf index (read))
  ;  (format t "You entered=>~A<=~%" index)
  (cond
   ((equal index 'QUIT) nil)
   ((not (integerp index))
    (progn
     (format t "Please enter an integer. ")
     (enter-location value low high)
     ))
   ((or (< index low) (> index high))
   (progn
    (format t "Please enter intergers in the range [~A, ~A]. " low high)
    (enter-location value low high)
    ))
   (t index))))


;; Process one step of the program to fill the array.
;; Again, notice the tail-recursion, which makes it practical to
;; implement this recursively without a stack overflow.
(defun one-step (value items)
 (print-items items)
 (let
  ((index (enter-location value 0 (- (length items) 1))))
  (if index
   (progn
    (setf (nth index items) value)
    (one-step (+ 1 value) items)
    ))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; main
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


; this hard-codes an array of length 10.  You, of course, will want to
; write functions to generate a row x column matrix
(setf items '(nil nil nil nil nil nil nil nil nil nil))

(one-step 0 items)
(format t "Good bye.")
