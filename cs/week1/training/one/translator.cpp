/* 题目：
*      翻译机
*  描述：
*      为了和外星人愉快的唠嗑，小C准备编写一个全能语言翻译机。他的目标是能够翻译
*  世界上所有的语言，让全世界、全宇宙的生物都无障碍交流！在热血澎湃的思考了一周以
*  后，他迈出了第一步。他准备先写一个简单的语言翻译机。
*      作为一个简单的翻译机，小C希望其能够帮助人类小A、计算机小B和小C进行愉快的交流。
*  下面是几个常见的话题：
*      关于星期
*          人类小A："Today is Monday/Tuesday/Wednesday/Thursday/Friday/Saturday/Sunday."
*          计算机小B："Var day=1/2/3/4/5/6/7;"
*          小C："Oh, my god. that's incredible. You know what? 
I just found that today is MMMonday/TTTuesday/WWWednesday/TTThursday/FFFriday/SSSaturday/SSSunday!"
*      关于今天的计划
*          人类小A："I want to XXX."
*          计算机小B："Var plan="XXX";"
*          小C："My god! What should I do today? Let me see. 
Well, I have an excellent idea! Let us go to XXX."
*          其中XXX为一个由空格和大小写字母组成的字符串。
*      关于点餐：
*          人类小A: "N XXX, please."
*          计算机小B: "Var item="XXX"; Var num=N;"
*          小C："I want one XXX, and one more, and one more, and one more …, 
and one more." (共N-1个"and one more")
*          其中N为一个整数，XXX为一个由空格和大小写字母组成的字符串。
*   现在，有小A、小B、小C中有两个相遇了，请你编写程序，将其中一位的话翻译给另外一位听。
*   输入格式
*       第一行为一个整数T，表示有T句话需要翻译。
*       接下来有T行，每行包含三个部分 X Y Z。其中X和Y为‘A’，‘B’，‘C’中的一种，
表示将X的话翻译到Y。(X,Y可能相同)。Z为一句由X说的话，格式如题意所述。
*   输出格式
*       对于每次翻译请求，输出翻译后的结果。
*   样例输入
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
*   样例输出
*       Var day=1;
*       Var plan="buy some eggs";
*       Var item="cola"; Var num=2;
*       Oh, my god. that's incredible. You know what? I just found that today is WWWednesday!
*       My god! What should I do today? Let me see. Well, I have an excellent idea! Let us go to shutdown.
*       I want one battery, and one more, and one more.
*       Today is Monday.
*       I want to eat the keyboard.
*       2 mountain, please.
*   数据范围
*       T ≤ 30
*   时间限制：1s
*   空间限制：512MB
*   提示
*       按照英语语法，可数名词单复数形式应不同。此处为了简便，忽略该语法，直接照搬原话中的词即可。
*   思路：
*       区分场景，找到能够代表不同场景的特征
*       区分不同人说话的特征
*       关键是提炼特征
*       将三种不同的说话人转为同一种中间状态，这种中间状态就是本程序自己的语言
*       用本程序自己的语言（即之前转换成的中间状态）翻译成不同说话人的风格，将其输出即可
*       通过转换成中间状态这种方式，要比直接点对点的翻译要高效，而且未来也可以适用于更多语言
*       用sscanf切分字符串，用sprintf组合字符串
*/