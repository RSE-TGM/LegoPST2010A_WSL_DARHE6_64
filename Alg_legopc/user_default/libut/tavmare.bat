acc -c tavmare.c > comp.out
lb /out:moduli.lib moduli.lib tavmare.obj >>comp.out
del tavmare.obj