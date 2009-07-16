#!/usr/bin/env python2.6

import os, sys

def main(prog, *args):
	if len(args) != 1:
		raise Exception("missing program name as parameter")

	lineiter = sys.stdin.xreadlines()
	for l in lineiter:
		if l.startswith("Len = "):
			sys.stdout.write(".")
			sys.stdout.flush()
			length = int(l[len("Len = "):])

			l = lineiter.next()
			if not l.startswith("Msg = "):
				raise Exception("bad file, expecting 'Msg = ' after 'Len = '");
			msg = l[len("Msg = "):].rstrip("\r\n")
			if length == 0:
				msg = ""
			if len(msg)*4 != length:
				raise Exception("bad msg, claimed length %d bits, have %d bytes = %d bits" % (length, len(msg), len(msg)*4))

			l = lineiter.next()
			if not l.startswith("MD = "):
				raise Exception("bad file, expecting 'MD = ' after 'Msg = '");
			exp = l[len("MD = "):].rstrip("\r\n")

			res = os.popen("echo -n %s | tr a-z A-Z | python -c 'import sys, base64; sys.stdout.write(base64.b16decode(sys.stdin.read()))' | %s" % (msg, args[0]), "r").read().rstrip("\n")
			if res != exp:
				print >>sys.stderr, "\nbad result\nexpected: %s\nsaw: %s\n" % (exp, res),
				sys.exit(1)
	print

if __name__ == "__main__":
	main(*sys.argv)
