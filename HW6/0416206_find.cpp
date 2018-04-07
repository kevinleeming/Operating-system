#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string>
#include <sys/stat.h> 
#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <sys/resource.h>

using namespace std;

void Find(char *pathname, vector<char *> op);

int main(int argc, char **argv){
	int i;
	vector<char *> opt;
	char *path;

	for(i = 0; i < argc; i++){
		if(i != 0){
			if(i == 1)
				path = argv[i];
			else{
				opt.push_back(argv[i]);
			}
		}
	}
	Find(path, opt);
	return 0;
}

void Find(char *pathname, vector<char *> op){
	DIR *dir;
	struct dirent *ptr;
	int i;

	if((dir = opendir(pathname)) == NULL){
		cout << "pathname doesn't exist" << endl;
		return;
	}
	while((ptr = readdir(dir)) != NULL){
		if(!strcmp(ptr->d_name, ".") || !strcmp(ptr->d_name, "..")) continue;

		char fpath[100];
		strcpy(fpath, pathname);
		int s;
		bool c = false;
		for(s = 0; s < 100; s++){
			if(fpath[s+1] == '\0'){
				if(fpath[s] != '/'){
					c = true;
					break;
				}
				else break;
			}
		}
		if(c){strcat(fpath, "/");}
		strcat(fpath, ptr->d_name);

		DIR *fdir;
		fdir = opendir(fpath);
		struct stat buf;
		if(stat(fpath, &buf))
			return;

		bool pass = true;
		for(i = 0; i < op.size(); i+=2){
			if(!strcmp(op[i], "-name")){
				if(strcmp(op[i+1], ptr->d_name)){
					pass = false;
				}
			}
			else if(!strcmp(op[i], "-inode")){
				int inode = atoi(op[i+1]);
				if(buf.st_ino != inode){
					pass = false;
				}
			}
			else if(!strcmp(op[i], "-size_max")){
				int size = atoi(op[i+1]);
				double fileSize = (double)size;
				for(int b = 0; b < 20; b++){
					fileSize *= 2;
				}
				if(buf.st_size > fileSize){
					pass = false;
				}
			}
			else if(!strcmp(op[i], "-size_min")){
				int size = atoi(op[i+1]);
				double fileSize = (double)size;
				for(int b = 0; b < 20; b++){
					fileSize *= 2;
				}
				if(buf.st_size < fileSize){
					pass = false;
				}
			}
		}
		double FileSize = (double)buf.st_size;
		for(int b = 0; b < 20; b++){
			FileSize /= 2;
		}
		if(pass){
			cout << fpath << " " << buf.st_ino << " " << FileSize << " MB" << endl;
		}
		if(fdir != NULL){
			Find(fpath, op);
		}
	}
}