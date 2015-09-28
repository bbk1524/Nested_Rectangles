# Code Notes

## Constructors vs init()
Constructors nice, but they tie the initialization of the object to the construction.
I'm going to use them, but with the following caveats:

- use a 'valid' bool that the constructor can set to false if needed and an is_valid() method to check.
- To separate the init from the constructor in classes that may change, use an init method that the constructor calls:

```
Object()
{
	this->valid = init();
}
```

- 