# Local-Dynamic-Arrays

## Example

```PAWN
strcpy(dest[], const source[], maxlength = sizeof dest)
{
    if(source[strlen(source)-1] == '\n')
	strmid(dest, source, 0, strlen(source)-1, maxlength);
    else strmid(dest, source, 0, strlen(source), maxlength);
    
    return 1;
}
```

```PAWN
main()
{
    new _tag:test_string = new[13];

    strcpy(_$test_string[0], "Hello World!");

    printf("%s", _$test_string[0]);
	
    delete[test_string];
}
```


