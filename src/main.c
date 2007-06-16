//insert file info....

//check if we have autoheader config.h, and include if necessary
#ifdef HAVE_CONFIG
#include <config.h>
#else
#define VERSION "1.0b"
#define PACKAGE "nesromtool"
#endif

#include<stdio.h>
#include<stdlib.h>

#include "types.h"
#include "commandline.h" /* for commandline parsing */
#include "NESutils.h"

// program options
//******************

// help
#define OPT_HELP 				"-?"
#define OPT_HELP_ALT 		"--help"

// verbose
#define OPT_VERBOSE 		"-v"
#define OPT_VERBOSE_ALT	"--verbose"

// version info
#define OPT_VERSION			"--version"
#define OPT_VERSION_ALT "" /* no alternate for version */

// set color palette
#define OPT_COLOR				"-c"
#define OPT_COLOR_ALT		"--color"
char color_palette[4] = "0136"; //default color palette for drawing sprites

// program commands
//*******************

//info
#define CMD_INFO				"info"

//title
#define CMD_TITLE				"title"

//prototypes
//*******************

//usage
void print_usage(char *app_name, bool extended);

//command parsing functions
void parse_cmd_info(char **argv);
void parse_cmd_title(char **argv);

int main (int argc, char *argv[]) {
	
	char *program_name = *argv;
	
	//check to see how many arguments we have... if no args, then print usage and bail
	if (argc == 1) {
		print_usage(program_name, false);
		exit(EXIT_FAILURE);
	}
	
	char *current_arg = NULL;
	
	//first, read program options... loop over args until we reach one that doesn't start with '-'
	for (current_arg = GET_NEXT_ARG ; (current_arg[0] == '-') ; current_arg = GET_NEXT_ARG) {

		// print help and quit
		if ( CHECK_ARG( OPT_HELP ) ) {
			print_usage(program_name, true);
			exit(EXIT_SUCCESS);
		}
		
		//print version and quit
		if ( CHECK_ARG( OPT_VERSION ) ) {
			printf("%s-%s\n\n", PACKAGE, VERSION);
			exit(EXIT_SUCCESS);
		}
		
		//set the color palette
		if ( CHECK_ARG( OPT_COLOR ) ) {
			printf("COLOR PALETTE NOT YET IMPLEMENTED!!\n");
			SKIP_NARG(1);
			continue; //go to next iteration of for() loop
		}
		
		//if we get here, we reached an unknown option
		printf("UNKNOWN OPTION: %s\n", *argv);
		exit(EXIT_FAILURE);
	}
	
	//if there is nothing else to do, print error and exit
	if (*argv == NULL) {
		printf("no command!\n");
		exit(EXIT_FAILURE);
	}
	
	//read command
	char *command = current_arg;
	printf("Command: %s\n", current_arg);
	
	SKIP_NARG(1);
	
	if (strcmp(command, CMD_INFO) == 0) {
		parse_cmd_info(argv);
	} else if (strcmp(command, CMD_TITLE) == 0) {
		parse_cmd_title(argv);
	}
	
	//end of program
	return 0;
}

void print_usage(char *app_name, bool extended) {
	/*
	**	program usage
	*/
	
		printf("\n");
		printf("%s-%s (http://nesromtool.sourceforge.net)\n", PACKAGE, VERSION);
		printf("Written by spike grobstein <spike@sadistech.com>\n\n");
		printf("USAGE: %s [options] <command> [command options] <file> [<file> ...]\n\n", app_name);
		
		if (extended) {
			printf("INSERT EXTENDED HELP HERE...\n\n");
		} else {
			printf("  Run '%s -?' for additional usage help\n\n", app_name);
		}
}

void parse_cmd_info(char **argv) {
	/*
	**	parses program arguments for the info command
	**	prints out various info about the ROM file...
	**		Filesize
	**		PRG/CHR counts
	**		title info
	**		filename
	**		
	*/
	
	//takes no options... so get right into reading filename(s)
	
	char *current_arg = *argv;
	
	if (current_arg == NULL) {
		printf("no filenames specified!\n");
		exit(EXIT_FAILURE);
	}
	
	for (; (current_arg != NULL) ; current_arg = GET_NEXT_ARG) {
		//current_arg is a filepath...
		FILE *ifile = NULL;
		
		//open the file for reading...
		if (!(ifile = fopen(current_arg, "r"))) {
			printf("Error opening file: %s\n", current_arg);
			exit(EXIT_FAILURE);
		}
		
		u32 filesize = NESGetFilesize(ifile); //get the filesize
		char human_filesize[32];
		hr_filesize(human_filesize, (double)filesize);
		
		//print info about the file
		printf("Filename:    %s\n", lastPathComponent(current_arg));
		printf("Filesize:    %ld bytes (%s)\n", filesize, human_filesize);
		
		printf("Verify:      ");
		if (NESVerifyROM(ifile)) {
			printf("OK\n");
		} else {
			//the file does not appear to be an NES ROM... so stop printing info and move on to next iteration of loop
			printf("ERROR\n");
			fclose(ifile);
			continue;
		}
		
		//print bank info
		printf("PRG Banks:   %d\n", NESGetPrgBankCount(ifile));
		printf("CHR Banks:   %d\n", NESGetChrBankCount(ifile));
		
		//print title info
		//outputs '[n/a]' if no title is found...
		char *title = (char*)malloc(NES_TITLE_BLOCK_LENGTH);
		NESGetTitle(title, ifile, 1);
		printf("Title:       %s\n", (title[0] != 0) ? title : "[n/a]");
		
		printf("\n");
		
		free(title);
		
		fclose(ifile);
	}
}

void parse_cmd_title(char **argv) {
	//continue parsing
	//loop over program arguments until we reach one that doesn't start with a '-', then those will be the file(s) to work on  
//	for (current_arg = GET_NEXT_ARG ; (current_arg[0] == '-') ; current_arg = GET_NEXT_ARG) {
		
//	}
}
