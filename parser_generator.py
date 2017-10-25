#!/usr/bin/python

import csv
import sys
from collections import defaultdict

def generate(rules, actions):
    # Header file
    f = open('parser_gen.h', 'w')

    f.write('''// auto-generated. DON'T MODIFY\n
/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#ifndef SSL_PARSER_GEN
#define SSL_PARSER_GEN

#include "lexer.h"

#define get_rule_len(r) rule[(r)][0]
#define get_rule_left(r) rule[(r)][1]

#define is_shift(p)     ((p)>0)
#define is_reduction(p) ((p)<0)
#define get_rule(p)     (-(p))

''')

    f.write('extern int rule[{}][2];\n'.format(len(rules)+1))
    f.write('extern int action[{}][{}];\n\n'.format(len(actions), len(actions[0])+10))

    non_terminals = set(v[0] for _, a in actions.iteritems() for v in a if not v[0].startswith('TOKEN_'))

    f.write('typedef enum {\n');
    f.write('  {} = TOKEN_NUM'.format(non_terminals.pop()))
    for symbol in non_terminals:
        f.write(', {}'.format(symbol))
    f.write('\n} t_nonterminal;\n\n');

    rules_cnt = defaultdict(int)
    rules_total = defaultdict(int)
    for _, (_, k) in rules.iteritems():
        rules_total[k] += 1

    f.write('enum {');
    for i, (_, (_, k)) in enumerate(rules.iteritems()):
        rule_name = 'RULE_' + k + '_' + str(rules_cnt[k])
        f.write('{}\n  {}'.format(',' if i != 0 else '', rule_name))
        rules_cnt[k] += 1
    f.write('\n};\n\n');

    f.write("void create_action_table();\n\n");
    f.write('#endif //SSL_PARSER')

    f.close()

    # Source file
    f = open('parser_gen.c', 'w')
    f.write('''// auto-generated. DON'T MODIFY\n
/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#include "parser_gen.h"

''')

    # Rules
    f.write('int rule[{}][2] = {{\n'.format(len(rules)+1))
    #f.write('  { 0, 0 },\n');
    for state, v in rules.iteritems():
        if state != 1:
            f.write(',\n');
        f.write('  {{ {}, {} }}'.format(*v))
    f.write('\n};\n\n')

    # Actions
    f.write('int action[{}][{}];\n\n'.format(len(actions), len(actions[0])+10))
    f.write('void create_action_table() {\n')

    for state, action in actions.iteritems():
        for k, v in action:
            v = int(v) if len(v) and v != "acc" else 0
            if v:
                f.write('  action[{}][{}] = {};\n'.format(state, k, v))
    f.write('};\n\n')

    f.close()


if __name__ == "__main__":
    if (len(sys.argv) != 3):
        print "Usage: parser_generator <rules_table.csv> <action_table.csv>"
        sys.exit()

    rules = {}
    rule = 1
    with open(sys.argv[1]) as f:
        reader = csv.reader(f)
        for row in reader:
            rules[rule] = row
            rule += 1

    actions = {}
    symbols = []
    action = 0
    with open(sys.argv[2]) as f:
        reader = csv.reader(f)
        symbols = reader.next()

        for row in reader:
            actions[action] = zip(symbols, row)
            action += 1

    generate(rules, actions)
