http://pages.cs.wisc.edu/~remzi/OSTEP/

[ostep.png](ostep.png)

```
hrefs = $($('table tbody tr table')[2])
	.find("a")
	.map(function(a,e){
		return e.href;
	};

copy(hrefs);
```
