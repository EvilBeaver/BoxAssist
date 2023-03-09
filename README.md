
# Box size calculation assist

Based on https://github.com/Infactum/addin-template by @Infactum

## Subsum problem

https://en.wikipedia.org/wiki/Subset_sum_problem

Here we need to find the indexes of the maximum size subset whose sum is equal to the given sum.

```

Input : [2, 3, 5, 10, 15, 20]
         sum  = 25
Output : "0,1,2,4"

```

## Usage

```Bsl
    MemoryStream = New MemoryStream();
    DataWriter = New DataWriter(MemoryStream);

    DataWriter.WriteInt16(2);
    DataWriter.WriteInt16(3);
    DataWriter.WriteInt16(5);
    DataWriter.WriteInt16(10);
    DataWriter.WriteInt16(15);
    DataWriter.WriteInt16(20);

    DataWriter.Close();
    Data = MemoryStream.CloseAndGetBinaryData();
    
    AttachAddIn("BoxAssist.dll", "BoxAssist");
    BoxAssist = New("AddIn.BoxAssist.BoxAssist");
    Output = BoxAssist.Calculate(Data, 25);
```
