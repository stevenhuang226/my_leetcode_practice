#include <stdio.h>
bool isMatch(char* s, char* p) {
	int sptr = 0, pptr = 0;
	char seeker = ' ';
	bool match;
	for ( int i = 0; i < strlen(s); i++ ) {
		if ( s[sptr] != p[pptr] && p[pptr] != '.' && skip = false ) {
			match = false;
			break;
		}
		else if ( skip == true && s[sptr] == seeker ) {
			for ( int ii = i; ii < strlen(s); ii++ ) {
			}
		}
		if ( pptr <= strlen(p) && p[pptr+1] == '*' ) {
			skip = true;
		}
		else if ( pptr+1 == strlen(p) ) {
			match = true;
		}
}
int main() {
	char* s = "test";
	char* p = "t..t";
	isMatch(s,p);
}
