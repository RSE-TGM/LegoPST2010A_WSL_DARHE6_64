# ******* Telelogic expanded section *******
all: ../bin/regopatch ../bin/regopatch.jar
	
../bin/regopatch: regopatch.sh
	cp  $? $@; chmod a+x $@

#../bin/regopatch.jar: Regopatch.java
#	$(JAVA_HOME)/bin/javac $? 
#	$(JAVA_HOME)/bin/jar -cvf $@ Regopatch.class
../bin/regopatch.jar: Regopatch.java
	javac $? 
	jar -cvf $@ Regopatch.class
