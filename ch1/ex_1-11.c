//Exercise 1-11: How would you test the word count program? What kinds of input are most likely to uncover bugs if there are any?

/*
	The tests would involve inputs with many of the characters which are tested for in the if/else loops:

		"\n\n\t\tthe\tquick\n\nbrown\tfox\n jumped \tover \nthe\t  lazy\n     dog\t ."

	Another idea is slightly incorrectly entered input:

		"The quick brown fox jumped over the lazy dog ."

	The inputs most likely to find bugs are those which are the longest and those containing many of the characters tested for, with very complicated arrangement. 
	Another idea is slightly incorrectly typed input (punctuation with accidental spaces before it would trick the program into increasing the word count).
*/
