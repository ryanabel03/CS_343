(load "lisp-unit.lisp")
(load "connect4_engine.lsp")

(define-test "make-board tests"
  (assert-equal '((nil nil nil nil)
                  (nil nil nil nil)
                  (nil nil nil nil)
                  (nil nil nil nil)) (make-board 4 4)))
(run-tests "make-board tests")
