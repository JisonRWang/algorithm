/* ��Ŀ��
*      �����
*  ������
*      Ϊ�˺�������������ྣ�СC׼����дһ��ȫ�����Է����������Ŀ�����ܹ�����
*  ���������е����ԣ���ȫ���硢ȫ��������ﶼ���ϰ�����������Ѫ���ȵ�˼����һ����
*  ���������˵�һ������׼����дһ���򵥵����Է������
*      ��Ϊһ���򵥵ķ������СCϣ�����ܹ���������СA�������СB��СC�������Ľ�����
*  �����Ǽ��������Ļ��⣺
*      ��������
*          ����СA��"Today is Monday/Tuesday/Wednesday/Thursday/Friday/Saturday/Sunday."
*          �����СB��"Var day=1/2/3/4/5/6/7;"
*          СC��"Oh, my god. that's incredible. You know what? 
I just found that today is MMMonday/TTTuesday/WWWednesday/TTThursday/FFFriday/SSSaturday/SSSunday!"
*      ���ڽ���ļƻ�
*          ����СA��"I want to XXX."
*          �����СB��"Var plan="XXX";"
*          СC��"My god! What should I do today? Let me see. 
Well, I have an excellent idea! Let us go to XXX."
*          ����XXXΪһ���ɿո�ʹ�Сд��ĸ��ɵ��ַ�����
*      ���ڵ�ͣ�
*          ����СA: "N XXX, please."
*          �����СB: "Var item="XXX"; Var num=N;"
*          СC��"I want one XXX, and one more, and one more, and one more ��, 
and one more." (��N-1��"and one more")
*          ����NΪһ��������XXXΪһ���ɿո�ʹ�Сд��ĸ��ɵ��ַ�����
*   ���ڣ���СA��СB��СC�������������ˣ������д���򣬽�����һλ�Ļ����������һλ����
*   �����ʽ
*       ��һ��Ϊһ������T����ʾ��T�仰��Ҫ���롣
*       ��������T�У�ÿ�а����������� X Y Z������X��YΪ��A������B������C���е�һ�֣�
��ʾ��X�Ļ����뵽Y��(X,Y������ͬ)��ZΪһ����X˵�Ļ�����ʽ������������
*   �����ʽ
*       ����ÿ�η���������������Ľ����
*   ��������
*       9
*       A B Today is Monday.
*       A B I want to buy some eggs.
*       A B 2 cola, please.
*       B C Var day=3;
*       B C Var plan="shutdown";
*       B C Var item="battery"; Var num=3;
*       C A Oh, my god. that's incredible. You know what? I just found that today is MMMonday!
*       C A My god! What should I do today? Let me see. Well, I have an excellent idea! Let us go to eat the keyboard.
*       C A I want one mountain, and one more.
*   �������
*       Var day=1;
*       Var plan="buy some eggs";
*       Var item="cola"; Var num=2;
*       Oh, my god. that's incredible. You know what? I just found that today is WWWednesday!
*       My god! What should I do today? Let me see. Well, I have an excellent idea! Let us go to shutdown.
*       I want one battery, and one more, and one more.
*       Today is Monday.
*       I want to eat the keyboard.
*       2 mountain, please.
*   ���ݷ�Χ
*       T �� 30
*   ʱ�����ƣ�1s
*   �ռ����ƣ�512MB
*   ��ʾ
*       ����Ӣ���﷨���������ʵ�������ʽӦ��ͬ���˴�Ϊ�˼�㣬���Ը��﷨��ֱ���հ�ԭ���еĴʼ��ɡ�
*   ˼·��
*       ���ֳ������ҵ��ܹ�����ͬ����������
*       ���ֲ�ͬ��˵��������
*       �ؼ�����������
*       �����ֲ�ͬ��˵����תΪͬһ���м�״̬�������м�״̬���Ǳ������Լ�������
*       �ñ������Լ������ԣ���֮ǰת���ɵ��м�״̬������ɲ�ͬ˵���˵ķ�񣬽����������
*       ͨ��ת�����м�״̬���ַ�ʽ��Ҫ��ֱ�ӵ�Ե�ķ���Ҫ��Ч������δ��Ҳ���������ڸ�������
*       ��sscanf�з��ַ�������sprintf����ַ���
*/