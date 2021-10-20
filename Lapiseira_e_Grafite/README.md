# Lapiseira e Grafite (enum, composição)
![](figura.jpg)

<!--TOC_BEGIN-->
- [Requisitos](#requisitos)
- [Shell](#shell)
- [Diagrama](#diagrama)
- [Esqueleto](#esqueleto)
<!--TOC_END-->

Faça o modelo de uma lapiseira que pode conter um único grafite.

## Requisitos
- Iniciar lapiseira
    - Inicia uma lapiseira de determinado calibre sem grafite.
- Inserir grafite
    - Insere um grafite passando
        - o calibre: float.
        - a dureza: string.
        - o tamanho em mm: int.
    - Não deve aceitar um grafite de calibre não compatível.
- Remover grafite
    - Retira o grafite se houver algum.
- Escrever folha
    - Não é possível escrever se não há grafite.
    - Quanto mais macio o grafite, mais rapidamente ele se acaba. Para simplificar, use a seguinte regra:
        - Grafite HB: 1mm por folha.
        - Grafite 2B: 2mm por folha.
        - Grafite 4B: 4mm por folha.
        - Grafite 6B: 6mm por folha.
        
    - Se o grafite acabar, defina o objeto grafite como `null`.
    - Se não houver grafite suficiente para terminar as folhas, avise que o texto ficou incompleto e informe quantas folhas completas foi possível escrever.
    - Avise quando o grafite acabar.


## Shell

```bash
#__case inserindo grafites
$init 0.5
$show
calibre: 0.5, grafite: null
$inserir 0.7 2B 50
fail: calibre incompatível
$inserir 0.5 2B 50
$show
calibre: 0.5, grafite: [0.5:2B:50]
$end
```

```bash
#__case inserindo e removendo
$init 0.3
$inserir 0.3 2B 50
$show
calibre: 0.3, grafite: [0.3:2B:50]
$inserir 0.3 4B 70
fail: ja existe grafite
$show
calibre: 0.3, grafite: [0.3:2B:50]
$remover
$inserir 0.3 4B 70
$show
calibre: 0.3, grafite: [0.3:4B:70]
$end
```

```bash
#__case escrevendo 1
$init 0.9
$inserir 0.9 4B 4
$write 1
warning: grafite acabou
$show
calibre: 0.9, grafite: null
$inserir 0.9 4B 30
$write 6
$show
calibre: 0.9, grafite: [0.9:4B:6]
$write 3
fail: folhas escritas completas: 1
warning: grafite acabou
$show
calibre: 0.9, grafite: null
$end
```

```bash
#__case escrevendo 2
$init 0.9
$inserir 0.9 2B 15
$show
calibre: 0.9, grafite: [0.9:2B:15]
$write 4
$show
calibre: 0.9, grafite: [0.9:2B:7]
$write 4
fail: folhas escritas completas: 3
warning: grafite acabou
$show
calibre: 0.9, grafite: null
$end
```


## Diagrama

![](diagrama.png)

***
## Esqueleto

<!--FILTER Solver.java java-->
```java

```
<!--FILTER_END-->