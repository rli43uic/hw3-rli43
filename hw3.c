void loop() {
	char * line;
	char ** args; //array of strings
	int status;
	
	do{
		printf("%s","CS361 >");
		line = read();
		args = parse(line);
		status = execute(args);

		free(line);
		free(args);
y
	}while(status);
}

int main (int argc, char** argv[]) {
	//load configuration files
	
	//runs a loop that reads the input	
	loop();

	return 0;
}
