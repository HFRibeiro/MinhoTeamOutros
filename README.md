# MinhoTeamOutros
Este repositório tem como finalidade ter todo o software que não se enquadre em nenhum dos já criados.
Todo o software que for adicionado deve ser colocado dentro de uma nova pasta!
E deve ser alterado este ficheiro de maneira a descrever o que faz esse novo software, e como se pode funcionar com ele, se tiver bibliotecas externas devem ser colocadas dentro dessa pasta e explicado aqui como instalar ou aceder a essas bibliotecas.


#AdjustLUT:
Este software foi criado para auxiliar o ajuste da LUT na camera dos robôs futebolistas, cria 4 ficheiros de texto com os valores selecionados através de trackbar. (campo.txt,linha.txt,bola.txt,obstaculo.txt)
*Utiliza as bibliotecas do OpenCv

#Full_Hardware_Teste
Este software foi criado para testar todo o hardware do robô futebolista, comunica diretamente com a porta série do robô de maneira a testar todas as suas funções.
*Utiliza as bibliotecas de SDL - Simple DirectMedia Layer e GLUT (OpenGL Utility Toolkit)

#LarPlayerBall:
Este software foi criado para ser mais facil a visualização da posição do robô e da bola de jogo, desenha o campo de futebol com as medidas do LAR, recebe os dados via UDP
*Não utiliza bibliotecas externas ao Qt

#LarPositionComands
Este software foi criado para ser possivel enviar o robo para coordenadas x,y do campo do LAR, para que o mesmo se movimente para essa posição, através de interface gráfica, após esse comando ser enviado recebe também o progresso do robô
*Não utiliza bibliotecas externas ao Qt

#LarReadString
Este software foi criado para ser possivel inserir uma string com as distancias do robô para as linhas à sua volta, e assim de obter a posição x,y do robô
*Não utiliza bibliotecas externas ao Qt

#NewSerial
Este software foi criado para ser o exemplo base de como fazer uma simples comunicação porta-serie
*Não utiliza bibliotecas externas ao Qt

#UDPRoboControl
Este software foi criado para ser possivel controlar o robo através de UDP e um joystick virtual
*Não utiliza bibliotecas externas ao Qt

#XML
Este software foi criado para ser o exemplo base de como usar XML no Qt
*Não utiliza bibliotecas externas ao Qt

