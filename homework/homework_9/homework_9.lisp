(defun is-palindrome(param)
  (equal param (reverse param)))

(defun intlist (a)
  (if (= a 1)
    '(1)
    (cons a (intlist(- a 1)))))

(defun rotate-left(l m)
  (setf result l)
  (dotimes (l m result)
    (setf result (append (rest result) (list (car result))))))


(defun evens(l)
  (if (<= (length l) 1)
    '()
    (if (evenp (length l))
      (append (evens (butlast l)) (last l)) (evens (butlast l)))))

(defun flatten (structure)
  (cond ((null structure) nil)
        ((atom structure) `(,structure))
        (t (mapcan #'flatten structure))))
