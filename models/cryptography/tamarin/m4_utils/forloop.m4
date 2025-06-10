divert(<!-1!>)
# forloop(var, from, to, stmt)
define(<!forloop!>, <!ifelse(eval(<!($2) <= ($3)!>), <!1!>,
  <!pushdef(<!$1!>)_$0(<!$1!>, eval(<!$2!>),
    eval(<!$3!>), <!$4!>)popdef(<!$1!>)!>)!>)
define(<!_forloop!>,
  <!define(<!$1!>, <!$2!>)$4<!!>ifelse(<!$2!>, <!$3!>, <!!>,
    <!$0(<!$1!>, incr(<!$2!>), <!$3!>, <!$4!>)!>)!>)
divert<!!>dnl
