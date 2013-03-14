(defun quad-roots (a b c)
  (let ((discriminant (- (* b b) (* 4 a c))))
    (values (/ (+ (- b) (sqrt discriminant)) (* 2 a))
            (/ (- (- b) (sqrt discriminant)) (* 2 a)))))

(defun gcd (a b)
  (if (= b 0)
    a
    (gcd b (mod a b))))
