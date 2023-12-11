# ThorNix Kernel

<p align="center">
  <a href="https://github.com/WesleyDev184/Thor-Shell" target="blank"><img src="https://cdn-icons-png.flaticon.com/512/1396/1396645.png" width="200" alt="Logo" /></a>
</p>

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)


## Descrição

O ThorNix Kernel é um projeto de kernel desenvolvido por motivos estudantis, criado para aprofundar o entendimento sobre sistemas operacionais e programação de baixo nível. Este kernel é uma iniciativa educacional e não é destinado a ambientes de produção.

## Recursos

- **Arquitetura:** x86 (32 bits)
- **Linguagem de Programação:** C e Assembly
- **Objetivo:** Aprofundar o conhecimento em sistemas operacionais e programação de kernel.

## Instruções de Compilação e Execução

1. **Requisitos:**

   - GCC (GNU Compiler Collection)
   - QEMU (emulador de máquina virtual)

2. **Compilação:**
   ```bash
   make
   ```
3. **Execução:**
   ```bash
   make run
   ```

## Estrutura do Projeto

- **boot:** Contém o código de boot do kernel.
- **drivers:** Contém os drivers de dispositivos.
- **include:** Contém os arquivos de cabeçalho.
- **kernel:** Contém o código do kernel.
- **lib:** Contém as bibliotecas do kernel.
- **scripts:** Contém os scripts de compilação.
- **test:** Contém os testes do kernel.
- **Makefile:** Arquivo de compilação do kernel.

## Contribuições

Contribuições são bem-vindas! Para contribuir, por favor, abra uma issue ou envie um pull request.

## Licença

Este projeto está licenciado sob a licença MIT. Para mais informações, por favor, leia o arquivo [GNU GENERAL PUBLIC LICENSE](https://www.gnu.org/licenses/gpl-3.0.html).
