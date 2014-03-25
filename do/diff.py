import sys, os, lib

out = sys.argv[1]
best = sys.argv[2]
fname = sys.argv[3]

with open(os.path.join(out, fname)) as f : lib.file.read(f, print)
with open(os.path.join(best, fname)) as f : lib.file.read(f, print)
