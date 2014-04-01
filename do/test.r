
args <- commandArgs(trailingOnly = TRUE)

a.cost <- read.table(args[1])$V1
b.cost <- read.table(args[2])$V1

t <- t.test (a.cost, b.cost, paired=T)$p.value
w <- wilcox.test (a.cost, b.cost, paired=T)$p.value

print(t)
print(w)